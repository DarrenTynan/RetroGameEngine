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
#include "../src/Systems/include/CameraMovementSystem.h"
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
#include "FileHandler/include/FileHandler.h"

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

std::shared_ptr<Registry> registry = std::make_shared<Registry>();
std::unique_ptr<AssetStore> assetStore = std::make_unique<AssetStore>();
std::unique_ptr<EventBus> eventBus = std::make_unique<EventBus>();

// Debug keyboard toggles
bool isCollider = true;
bool isRayCast = false;
bool isCamera = true;

bool isDebugWindow = true;

static SDL_Window* debugWindow;
static SDL_Renderer* debugRenderer;

uint32_t msSincePreviousFrame = 0;

// Lua
sol::state lua;

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
    std::ifstream file(filePath);

    // Check if the file is open.
    if ( !file.is_open()) exit(1);

    // Read the entire file into a string
    std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Create a Document object to hold the JSON data of the config file
    rapidjson::Document gameConfig;

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
    registry->AddSystem<CameraMovementSystem>();          // Check the camera move system
    registry->AddSystem<ProjectileEmitSystem>();          // Check entity bullets AABB
    registry->AddSystem<ProjectileLifecycleSystem>();     // Check the life cycle and kill off bullets
    registry->AddSystem<RenderColliderSystem>();          // Debug updateRender collision box's
    registry->AddSystem<RenderSystem>();                  // Render windows
    registry->AddSystem<RenderTextSystem>();              // Render any label's
//    registry->AddSystem<RenderRaycastSystem>();           // Debug updateRender the ray cast's
    registry->AddSystem<ScriptSystem>();                  // Lua scripting system

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
            gameConfig["configuration"]["window_title"].GetString(),
            SDL_WINDOWPOS_CENTERED,
            0,          //SDL_WINDOWPOS_CENTERED,
            gameConfig["configuration"]["window_width"].GetInt(),
            gameConfig["configuration"]["window_height"].GetInt(),
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
    gameCamera = {0, 32*11, gameConfig["configuration"]["window_width"].GetInt(), gameConfig["configuration"]["window_height"].GetInt() };


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
                550,
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
        registry->GetSystem<CameraMovementSystem>().Update(gameRenderer, gameCamera);
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
    }
    return isQuit;
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
//    registry->GetSystem<Ent ityCollisionSystem>().Update(eventBus);

    /**
     * @brief Projectile updates.
     */
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();

    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CameraMovementSystem>().Update(gameRenderer, gameCamera);
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
    auto fsm = rigidBody.fsm;

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

