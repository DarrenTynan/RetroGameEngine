//
// Created by Darren Tynan on 17/11/2024.
//

#include <string>
#include <filesystem>
#include <thread>
#include <unistd.h>
#include "../include/RGE.h"
#include "Systems/include/ScriptSystem.h"
#include "LevelLoader/include/LevelLoader.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "../src/EventBus/include/EventBus.h"
#include "../src/Systems/include/PlayerControllerSystem.h"
#include "../src/Systems/include/CameraFollowSystem.h"
#include "../src/Systems/include/EntityMovementSystem.h"
#include "../src/Systems/include/RenderSystem.h"
#include "../src/Systems/include/RenderTextSystem.h"
#include "../src/Systems/include/RenderColliderSystem.h"
#include "../src/Systems/include/AnimationSystem.h"
#include "../src/Systems/include/PlayerCollisionSystem.h"
#include "../src/Systems/include/EntityCollisionSystem.h"
#include "../src/Systems/include/ProjectileEmitSystem.h"
#include "../src/Systems/include/ProjectileLifecycleSystem.h"
#include "../src/Systems/include/DamageSystem.h"
#include "../src/Systems/include/RenderRaycastSystem.h"
#include "../src/Systems/include/EditorSystem.h"
#include "FileHandler/include/FileHandler.h"
#include "include/SpritesheetComponent.h"
#include "../../Editor/include/Editor.h"

using namespace EDITOR;
using namespace RGE_ECS;
using namespace RGE_Component;
using namespace RGE_AssetStore;
using namespace RGE_EventBus;
using namespace RGE_Events;
using namespace RGE_FILEHANDLER;
using namespace RGE_LevelLoader;

SDL_Window* gameWindow;
SDL_Rect gameCamera;
SDL_Renderer* gameRenderer;

SDL_Window *editorWindow;
SDL_Renderer *editorRenderer;
ImGuiIO io;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

std::shared_ptr<DisplayHolder> pDisplayHolder = std::make_shared<DisplayHolder>();
std::shared_ptr<Registry> registry = std::make_shared<Registry>();
std::unique_ptr<AssetStore> assetStore = std::make_unique<AssetStore>();
std::unique_ptr<EventBus> eventBus = std::make_unique<EventBus>();

// Debug keyboard toggles
bool isCollider = true;
// TODO NOT to be used as not working!
bool isRayCast = false;
bool isCamera = true;
bool isDebugWindow = false;

static SDL_Window* debugWindow;
static SDL_Renderer* debugRenderer;

uint32_t msSincePreviousFrame = 0;

// Every Lua program runs within a Lua state, which is a container for the Lua interpreter's data,
// including global variables, functions, and other objects
sol::state lua;

// Create a Document object to hold the JSON data of the config file
rapidjson::Document gameConfig;

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

/**
 * @file RGE.cpp
 *
 * @brief Load the config.json file so we can set the game window title and size.
 * Initialise the registry with systems. Set up the Lua level loader system.
 */
void RGE::Setup()
{
    // Get the current working dir and concatenate the config filename.
    std::string rootDir = std::filesystem::current_path();
    std::string filePath = rootDir  + "/GameConfig.json";
    std::cout << "Current path is " << filePath << '\n';

    // Load the config file
//    std::ifstream file(filePath);
    std::ifstream file("/Users/darren/Development/C++_Projects/RetroGameEngine/Engine_Test_Game_Platform/GameConfig.json");

    // Check if the file is open.
    if ( !file.is_open()) exit(1);

    // Read the entire file into a string
    std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Parse the JSON data
    gameConfig.Parse(json.c_str());

    // Check for parse errors
    if (gameConfig.HasParseError())
    {
        std::cerr << "Error parsing JSON: " << gameConfig.GetParseError() << std::endl;
        exit(1);
    }

    // Add the systems that need to be processed in our game
    registry->AddSystem<EntityMovementSystem>();          // Move all entities
    registry->AddSystem<PlayerControllerSystem>();        // Move the player & apply forces
    registry->AddSystem<AnimationSystem>();               // Animate all entities
    registry->AddSystem<PlayerCollisionSystem>();         // Check all entity collisions AABB
    registry->AddSystem<EntityCollisionSystem>();         // Check all entity collisions AABB
    registry->AddSystem<DamageSystem>();                  // Check all damage systems
    registry->AddSystem<CameraFollowSystem>();            // Check the camera move system
    registry->AddSystem<ProjectileEmitSystem>();          // Check entity bullets AABB
    registry->AddSystem<ProjectileLifecycleSystem>();     // Check the life cycle and kill off bullets
    registry->AddSystem<RenderColliderSystem>();          // Debug updateRender collision box's
    registry->AddSystem<RenderSystem>();                  // Render windows
    registry->AddSystem<RenderTextSystem>();              // Render any label's
//    registry->AddSystem<RenderRaycastSystem>();           // Debug updateRender the ray cast's
    registry->AddSystem<ScriptSystem>();                  // Lua scripting system

    registry->AddSystem<EditorSystem>();         // Link system to the ImGui editor

    // Create the bindings between C++ and Lua
    registry->GetSystem<ScriptSystem>().CreateLuaBindings(lua);


    // Use all the libraries
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);

    // Setup SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL could not be initialised\n" << SDL_GetError();
        exit(1);
    }

    // Setup true type fonts
    if (TTF_Init() != 0)
    {
        std::cout << "SDL TTF's could not be initialised\n" << SDL_GetError();
        exit(1);
    }

    // From 2.0.18: Enable native IME.
    #ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

    // Create window with SDL_Renderer graphics context
    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    gameWindow = SDL_CreateWindow(
            gameConfig["window_title"].GetString(),
            SDL_WINDOWPOS_CENTERED,
            110,          //SDL_WINDOWPOS_CENTERED,
            gameConfig["graphics"]["resolution"]["window_width"].GetInt(),
            gameConfig["graphics"]["resolution"]["window_height"].GetInt(),
            windowFlags
    );

    if (!gameWindow)
    {
        std::cout << "Window game init failed" << std::endl;
        SDL_Quit();
        exit(1);
    }

    gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!gameRenderer)
    {
        std::cout << "Window renderer init failed" << std::endl;
        SDL_DestroyRenderer(gameRenderer);
        SDL_Quit();
        exit(1);
    }

    // SetupSDL the camera view with the entire screen area
    gameCamera = {0, 32*11, gameConfig["graphics"]["resolution"]["window_width"].GetInt(), gameConfig["graphics"]["resolution"]["window_height"].GetInt() };


    /**
     * @brief A simple debug info window.
     */
    if (isDebugWindow)
    {
        // Create window with SDL_Renderer graphics context
        auto windowFlags2 = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
        debugWindow = SDL_CreateWindow(
                "Debug Window",
                0,
                0,
                400,
                350,
                windowFlags2
        );

        if (!debugWindow)
        {
            std::cout << "Window game init failed" << std::endl;
            SDL_Quit();
            exit(1);
        }

        debugRenderer = SDL_CreateRenderer(debugWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!debugRenderer)
        {
            std::cout << "Window renderer init failed" << std::endl;
            SDL_DestroyRenderer(debugRenderer);
            SDL_Quit();
            exit(1);
        }

    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    // Create window with SDL_Renderer graphics context
    auto windowFlags3 = (SDL_WindowFlags)( SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_ALLOW_HIGHDPI );
    auto windowFlags4 = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
    editorWindow = SDL_CreateWindow(
            "Retro Game_Engine Engine v1",
            0,
            0,
            displayMode.w,
            displayMode.h,
            windowFlags4
    );

    if (!editorWindow)
    {
        LOGGER::TerminalLogger::Error("Window init failed", 0);
        SDL_Quit();
        exit(1);
    }

    editorRenderer = SDL_CreateRenderer(editorWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!editorRenderer)
    {
        LOGGER::TerminalLogger::Error("Window renderer init failed", 0);
        SDL_DestroyRenderer(editorRenderer);
        SDL_Quit();
        exit(1);
    }


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // enable docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 5.3f;
    style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 0;

    style.Colors[ImGuiCol_Tab] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);

    style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 0.50f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(editorWindow, editorRenderer);
    ImGui_ImplSDLRenderer2_Init(editorRenderer);

    io.Fonts->AddFontFromFileTTF("../Editor/fonts/Pixellettersfull.ttf", 18.f);

    // Instantiate the display windows via magic pointers
    auto pMainMenuBar = std::make_unique<MainMenuBar>();
    auto pTestDisplayA = std::make_unique<TestDisplayA>();
    auto pTestDisplayB = std::make_unique<EntityDisplay>();
    auto pMouseDisplay = std::make_unique<MouseDisplay>();
    auto pLogDisplay = std::make_unique<LogDisplay>();
    auto pFileDisplay = std::make_unique<FileDisplay>();
//        auto pProjectMenuDisplay = std::make_unique<ProjectMenuDisplay>();

    // Add display class's to the vector array in IDisplay
    pDisplayHolder->displays.push_back( std::move(pMainMenuBar) );
    pDisplayHolder->displays.push_back( std::move(pTestDisplayA) );
    pDisplayHolder->displays.push_back( std::move(pTestDisplayB) );
    pDisplayHolder->displays.push_back( std::move(pMouseDisplay) );
    pDisplayHolder->displays.push_back( std::move(pLogDisplay) );
    pDisplayHolder->displays.push_back( std::move(pFileDisplay) );
//        pDisplayHolder->displays.push_back( std::move(pProjectMenuDisplay) );

    auto logger = EDITOR_LOGGER::Logger::GetInstance();
    logger->Clear();
    logger->AddLog("All systems should be up and running...\n");

    SetupPlayer();

}


/**
 * @brief Setup player from the game config.json file.
 */
 void RGE::SetupPlayer()
{
    Entity newEntity = registry->CreateEntity();

    if (gameConfig["player"].HasMember("tag"))
        newEntity.AddTag(gameConfig["player"]["tag"].GetString());

    if (gameConfig["player"].HasMember("transform"))
    {
        newEntity.AddComponent<TransformComponent>(
                glm::vec2( gameConfig["player"]["transform"]["start_position_x"].GetFloat(), gameConfig["player"]["transform"]["start_position_y"].GetFloat() ),
                glm::vec2( gameConfig["player"]["transform"]["scale_x"].GetFloat(), gameConfig["player"]["transform"]["scale_y"].GetFloat() ),
                gameConfig["player"]["transform"]["rotation"].GetFloat()
        );
    }

    if (gameConfig["player"].HasMember("rigidbody"))
    {
        newEntity.AddComponent<RigidBodyComponent>(
                glm::vec2( gameConfig["player"]["rigidbody"]["deltaXY_x"].GetFloat(), gameConfig["player"]["rigidbody"]["deltaXY_y"].GetFloat() ),
                glm::vec2( gameConfig["player"]["rigidbody"]["maxDeltaXY_x"].GetFloat(), gameConfig["player"]["rigidbody"]["maxDeltaXY_y"].GetFloat() ),
                gameConfig["player"]["rigidbody"]["acceleration"].GetFloat(),
                gameConfig["player"]["rigidbody"]["boost"].GetFloat(),
                gameConfig["player"]["rigidbody"]["gravity"].GetFloat(),
                gameConfig["player"]["rigidbody"]["friction"].GetFloat()
        );
    }

    if (gameConfig["player"].HasMember("box_collider"))
    {
        newEntity.AddComponent<BoxColliderComponent>(
                gameConfig["player"]["box_collider"]["width"].GetFloat(),
                gameConfig["player"]["box_collider"]["height"].GetFloat(),
                glm::vec2(gameConfig["player"]["box_collider"]["position_x"].GetFloat(), gameConfig["player"]["box_collider"]["position_y"].GetFloat() ),
                gameConfig["player"]["box_collider"]["has_ray_cast"].GetBool()
        );
    }

    if (gameConfig["player"].HasMember("sprite"))
    {
        newEntity.AddComponent<SpriteComponent>(
                gameConfig["player"]["sprite"]["texture_asset_id"].GetString(),
                gameConfig["player"]["sprite"]["frame_width"].GetInt(),
                gameConfig["player"]["sprite"]["frame_height"].GetInt(),
                gameConfig["player"]["sprite"]["z_index"].GetInt(),
                gameConfig["player"]["sprite"]["isFixed"].GetBool(),
                gameConfig["player"]["sprite"]["flipH"].GetBool(),
                gameConfig["player"]["sprite"]["src_rect_x"].GetFloat(),
                gameConfig["player"]["sprite"]["src_rect_y"].GetFloat()
        );
    }

    if (gameConfig["player"].HasMember("animation"))
    {
        newEntity.AddComponent<AnimationComponent>(
                gameConfig["player"]["animation"]["num_frames"].GetInt(),
                gameConfig["player"]["animation"]["fps"].GetInt(),
                gameConfig["player"]["animation"]["is_loop"].GetBool()
        );
    }

    if (gameConfig["player"]["player_states"].HasMember("states"))
    {
        newEntity.AddComponent<SpritesheetComponent>();

        for (int i = 0; i < gameConfig["player"]["player_states"]["num_of_states"].GetInt(); ++i)
        {
            std::cout << gameConfig["player"]["player_states"]["states"][i]["name"].GetString() << std::endl;
            newEntity.GetComponent<SpritesheetComponent>().AddToSheet(
                    i,
                    gameConfig["player"]["player_states"]["states"][i]["name"].GetString(),
                    gameConfig["player"]["sprite"]["frame_width"].GetInt(),
                    gameConfig["player"]["sprite"]["frame_height"].GetInt(),
                    gameConfig["player"]["sprite"]["z_index"].GetInt(),
                    gameConfig["player"]["sprite"]["isFixed"].GetBool(),
                    gameConfig["player"]["player_states"]["states"][i]["start_frame_x"].GetInt() * 32,
                    gameConfig["player"]["player_states"]["states"][i]["start_frame_y"].GetInt() * 32,
                    gameConfig["player"]["player_states"]["states"][i]["num_frames"].GetInt(),
                    gameConfig["player"]["player_states"]["states"][i]["fps"].GetInt(),
                    gameConfig["player"]["player_states"]["states"][i]["is_loop"].GetBool()
            );
        }
    }

    if (gameConfig["player"].HasMember("camera_follow"))
    {
        newEntity.AddComponent<CameraFollowComponent>(40,
                                                      22,
                                                      32,
                                                      gameConfig["player"]["transform"]["start_position_x"].GetFloat(),
                                                      gameConfig["player"]["transform"]["start_position_y"].GetFloat()
        );
    }

}


/**
  * @brief Initialise the assetStore with pointers to png.
 */
void RGE::LoadLevel()
{
    // Load the entity data for level 1
    LevelLoader::LoadLevel(lua, registry, assetStore, gameRenderer, 1);
}


/**
 * @brief Call updateRender on all objects
 */
void RGE::UpdateRenderer()
{
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gameRenderer);

    // Invoke all the systems that need to updateRender
    registry->GetSystem<RenderSystem>().Update(gameRenderer, assetStore, gameCamera);
    registry->GetSystem<RenderTextSystem>().Update(gameRenderer, assetStore, gameCamera);

    if (isCamera)
    {
        registry->GetSystem<CameraFollowSystem>().Update(gameRenderer, gameCamera);
    }

    if (isCollider)
    {
        registry->GetSystem<RenderColliderSystem>().Update(gameRenderer, gameCamera);
    }

    if (isRayCast)
    {
        auto player = registry->GetEntityByTag("player");
        registry->GetSystem<RenderRaycastSystem>().Update(gameRenderer, player);
    }

    if (isDebugWindow)
        DebugWindowText();

    int windowWidth = gameConfig["graphics"]["resolution"]["window_width"].GetInt();
    int windowHeight = gameConfig["graphics"]["resolution"]["window_height"].GetInt();

    int x1 = 0;
    int y1 = 0;
    int x2 = windowWidth;
    int y2 = 0;
    SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0x00, 0x00, 0xFF );

    // Horizontal
    for (int i = 0; i <= windowHeight / 32; ++i)
    {
        SDL_RenderDrawLine(gameRenderer, x1, y1, x2, y2);
        y1 = y1 + 32;
        y2 = y2 + 32;
    }

    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = windowHeight;
    SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0x00, 0x00, 0xFF );

    // Vertical
    for (int i = 0; i <= windowWidth / 32; ++i)
    {
        SDL_RenderDrawLine(gameRenderer, x1, y1, x2, y2);
        x1 = x1 + 32;
        x2 = x2 + 32;
    }

    // Render all graphics onto screen.
    SDL_RenderPresent(gameRenderer);

}


/**
 * @brief Poll window and keyboard events
 * @details If the cursor key's are pressed then emit a Walk<XX>Event
 */
bool RGE::ProcessKeyboardInputs()
{
    bool isQuit = true;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Set docking to main viewport
        ImGui::DockSpaceOverViewport();

        // Render the editor display panels.
        for ( const auto& pDisplay : pDisplayHolder->displays )
        {
            pDisplay->Render(registry);
        }

        ImGui::ShowDemoWindow();

        // Rendering
        ImGui::Render();
        SDL_RenderSetScale(editorRenderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(editorRenderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
                               (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(editorRenderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), editorRenderer);
        SDL_RenderPresent(editorRenderer);

        // Core sdl events.
        switch (sdlEvent.type)
        {
            // Window close
            case SDL_QUIT:
                isQuit = false;
                break;

            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { isQuit = false; }
                if (sdlEvent.key.keysym.sym == SDLK_c) { isCollider = !isCollider; }
                if (sdlEvent.key.keysym.sym == SDLK_r) { isRayCast = !isRayCast; }

                if (sdlEvent.key.keysym.sym == SDLK_SPACE)
                {
                    eventBus->EmitEvent<JumpEvent>(sdlEvent.key.keysym.sym);
                }

                if (sdlEvent.key.keysym.sym == SDLK_p) { sleep(10); }

                break;
        }


//        void HandleButtonEvent(SDL_MouseButtonEvent& E) {
//            if (E.button == SDL_BUTTON_LEFT) {
//                 The left button was pressed or released
//            } else if (E.button == SDL_BUTTON_RIGHT) {
//                 The right button was pressed or released
//            }




        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            if (HasWindowFocus(gameWindow))
            {
                auto logger = EDITOR_LOGGER::Logger::GetInstance();
                logger->AddLog("RGE Mouse Pressed...\n");
                registry->GetSystem<EditorSystem>().MousePressed(registry, gameCamera);
            }

        }
    }
    return isQuit;
}


bool RGE::HasWindowFocus(SDL_Window* window)
{
    uint32_t flags = SDL_GetWindowFlags(window);
    // We *don't* want to check mouse focus:
    // SDL_WINDOW_INPUT_FOCUS - input is going to the window
    // SDL_WINDOW_MOUSE_FOCUS - mouse is hovered over the window, regardless of window focus
    return (flags & SDL_WINDOW_INPUT_FOCUS) != 0;
}


/**
 * @brief Update all the systems.
 */
void RGE::UpdateSystems()
{
    // The difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - msSincePreviousFrame) / 1000.0;

    // Store the "previous" frame time
    msSincePreviousFrame = SDL_GetTicks();

    // Reset all event handlers for the current frame
    eventBus->Reset();

    /**
     * @brief Subscribe to events
     */
    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<PlayerControllerSystem>().SubscribeToEvents(eventBus, registry);
    registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventBus);

    // UpdateSystems the registry to process the entities that are waiting to be created/deleted
    registry->Update();

    /**
     * @brief Apply deltaXY and check out of bounds.
     */
//    registry->GetSystem<EntityMovementSystem>().Update(deltaTime);
    registry->GetSystem<PlayerControllerSystem>().Update(deltaTime, gameCamera);

    /**
     * @brief AABB collision player to all other objects.
     */
    registry->GetSystem<PlayerCollisionSystem>().Update(eventBus, registry, gameCamera);
//    registry->GetSystem<EntityCollisionSystem>().Update(eventBus);

    /**
     * @brief Projectile updates.
     */
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();

    registry->GetSystem<AnimationSystem>().Update();

    registry->GetSystem<CameraFollowSystem>().Update(gameRenderer, gameCamera);
    registry->GetSystem<RenderTextSystem>().Update(gameRenderer, assetStore, gameCamera);

}


/**
 * @brief Destroy the SDL renderer and window.
 */
void RGE::Destroy()
{
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);

    if (isDebugWindow)
    {
        SDL_DestroyRenderer(debugRenderer);
        SDL_DestroyWindow(debugWindow);
    }

    SDL_Quit();
}


/**
 * @brief Debug window
 */
void RGE::DebugWindowText()
{
    SDL_SetRenderDrawColor(debugRenderer, 10, 147, 248, 255);
    SDL_RenderClear(debugRenderer);

    auto player = registry->GetEntityByTag("player");
    auto transform = player.GetComponent<TransformComponent>();
    auto rigidBody = player.GetComponent<RigidBodyComponent>();
    auto boxCollider = player.GetComponent<BoxColliderComponent>();
    auto &fsmComponent = player.GetComponent<FSMComponent>();
    auto fsm = fsmComponent.getFsm();

    TTF_Font* Chariot = TTF_OpenFont("/Users/darren/Development/C++_Projects/RetroGameEngine/Engine/fonts/arial.ttf", 18);
    SDL_Color White = {255, 255, 255};

    std::string text;
    text = "pos.x: " + std::to_string(transform.position.x) + " pos.y: " + std::to_string(transform.position.y)
           + "\nrb->dx: " + std::to_string(rigidBody.deltaXY.x) + " rb->dy: " + std::to_string(rigidBody.deltaXY.y)
           + "\nrb->mdx: " + std::to_string(rigidBody.maxDeltaXY.x) + " rb->mdy: " + std::to_string(rigidBody.maxDeltaXY.y)
           + "\nfsm->dir.x: " + std::to_string(fsm->direction.x) + " fsm->dir.y: " + std::to_string(fsm->direction.y)
           + "\nfsm->current state: " + fsm->getCurrentState()->getName()
           + "\ncamera.x: " + std::to_string(gameCamera.x) + " camera.y: " + std::to_string(gameCamera.y)
           + "\ncamera.w: " + std::to_string(gameCamera.w) + " camera.h: " + std::to_string(gameCamera.h)
           + "\nfsm->isGrounded: " + std::to_string(fsm->isGrounded)
           + "\nbox.x: " + std::to_string(boxCollider.center.x) + " box.y: " + std::to_string(boxCollider.center.y)
           + "\nbox.w: " + std::to_string(boxCollider.width) + " box.h: " +std::to_string(boxCollider.height)
           ;

    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(Chariot, text.c_str(), White, 400);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(debugRenderer, surface);
    SDL_FreeSurface(surface);

    int labelWidth = 0;
    int labelHeight = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &labelWidth, &labelHeight);
    SDL_Rect dstRect = {
            8,
            0,
            labelWidth,
            labelHeight
    };

    SDL_RenderCopy(debugRenderer, texture, nullptr, &dstRect);
    SDL_RenderPresent(debugRenderer);
    SDL_DestroyTexture(texture);
}

