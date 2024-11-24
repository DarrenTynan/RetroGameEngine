//
// Created by Darren Tynan on 26/12/2022.
//

#include "Game.h"
#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "glm/glm.hpp"

#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/PlayerControllerComponent.h"
//#include "../Components/StateMachineComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/RaycastComponent.h"

#include "../Systems/CameraMovementSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../Systems/RenderColliderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/PlayerControlSystem.h"
#include "../Systems/RenderImGuiSystem.h"
//#include "../Systems//StateMachineSystem.h"
#include "../Systems/ProjectileEmitSystem.h"
#include "../Systems/ProjectileLifecycleSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/RenderRaycastSystem.h"

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

//#include <lua/lua.hpp>
//#include <sol/sol.hpp>
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "../libs/box2d/box2d.h"

int Game::windowWidth;
int Game::windowHeight;
int Game::mapWidth;
int Game::mapHeight;

const auto MAP_PATH = "../assets/tilemaps/Level_01.tmx";
std::string mapImagePath;
tmx::Map map;

Game::Game()
{
    isRunning = false;
    isDebug = false;
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
    eventBus = std::make_unique<EventBus>();
    Logger::Log("Game constructor called");
}

Game::~Game() { Logger::Log("Game deconstruct called"); }

/**
 * Initialise:
 *
 * Init the game SDL2 window and set camera vars.
 *
 * sdl window
 * set isRunning to true
 */
void Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        std::cout << "SDL could not be initialised\n" << SDL_GetError();
        return;
    }

    if (TTF_Init() != 0)
    {
        Logger::Error("Error initializing SDL TTF");
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
        windowWidth = 640;
        windowHeight = 480;
//    windowWidth = displayMode.w;
//    windowHeight = displayMode.h;

    window = SDL_CreateWindow(
            "Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_SHOWN
            );

    if (!window)
    {
        std::cerr << "Window init failed" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "Window renderer init failed" << std::endl;
        return;
    }

    // Initialize the camera view with the entire screen area
    camera.x = 0;
    camera.y = 0;
    camera.w = windowWidth;
    camera.h = windowHeight;

    std::cout << "SDL is ready to go!\n";
//    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

}


/**
 * Poll events:
 *
 * window quit
 * keyboard
 */
void Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        // ImGui
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        ImGuiIO io = ImGui::GetIO();
        int mouseX;
        int mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
        io.MousePos = ImVec2(mouseX, mouseY);
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

        if (sdlEvent.type == SDL_KEYUP)
        {
           eventBus->EmitEvent<KeyReleasedEvent>(sdlEvent.key.keysym.sym);
        }

        // Core sdl events.
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                if (sdlEvent.key.keysym.sym == SDLK_d)
                {
                    isDebug = !isDebug;
                }
                if (sdlEvent.key.keysym.sym == SDLK_g)
                {
                    isImGui = !isImGui;
                }
                eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
                break;
        }
    };
};

/**
 * Load the tmx map files and iterate over.
 *
 * @return
 */
int Game::GetTMX()
{
    map.load(MAP_PATH);

    if(map.load(MAP_PATH))
    {
        const auto& layers = map.getLayers();
        for(const auto& layer : layers)
        {
            if(layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                for(const auto& object : objects)
                {
                    //do stuff with object properties
                    Entity tile = registry->CreateEntity();
                    tile.AddComponent<BoxColliderComponent>(object.getAABB().width, object.getAABB().height);
                    tile.AddComponent<TransformComponent>(glm::vec2(object.getAABB().left,  object.getAABB().top));

                }
            }
            else if(layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                //read out tile layer properties etc...

                const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();

                const auto& imagePath = map.getTilesets();
                mapImagePath = imagePath[0].getImagePath();

                // Tile width in pixels (32)
                unsigned int tileWidth = map.getTileSize().x;
                // Tile height in pixels (32)
                unsigned int tileHeight = map.getTileSize().x;
                // Image width
                unsigned int imageWidth = map.getTilesets().size();

                // How many tiles per row (25)
                unsigned int tileCountX = map.getTileCount().x;
                mapWidth = map.getTileCount().x * tileWidth;
                // How many tiles per column (20)
                unsigned int tileCountY = map.getTileCount().y;
                mapHeight = map.getTileCount().y * tileHeight;

                int index = 0;
                for (int y = 0; y < tileCountY; y++) {
                    for (int x = 0; x < tileCountX; x++) {
                        // Get the source rect pixel x,y position.
                        int tilesPerRow = imagePath[0].getImageSize().x / tileWidth;
                        int firstgid = 1;
                        int srcRectX = ( (tiles[index].ID - firstgid) % tilesPerRow )  * tileWidth;
                        int srcRectY = ( (tiles[index].ID - firstgid) / tilesPerRow ) * tileHeight;

                        Entity tile = registry->CreateEntity();

                        tile.AddComponent<TransformComponent>(glm::vec2(x * tileWidth, y * tileHeight), glm::vec2(1, 1), 0.0);
                        tile.AddComponent<SpriteComponent>("tilemap-image", tileWidth, tileHeight, 0, true, false, srcRectX, srcRectY);
//                        tile.AddComponent<BoxColliderComponent>(32,32);
                        index++;
                    }
                }
            }
        }

        const auto& tilesets = map.getTilesets();
        for(const auto& tileset : tilesets)
        {
            //read out tile set properties, load textures etc...
        }
    }

    return 0;
}


/**
 * Initialise game objects
 */
void Game::SetUpGameObjects()
{
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<RenderTextSystem>();
    registry->AddSystem<RenderColliderSystem>();
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<PlayerControlSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<RenderImGuiSystem>();
//    registry->AddSystem<StateMachineSystem>();
    registry->AddSystem<ProjectileEmitSystem>();
    registry->AddSystem<ProjectileLifecycleSystem>();
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<RenderRaycastSystem>();

    // Load the tilemap
    GetTMX();

    // Adding assets to the asset store
    assetStore->AddTexture(renderer, "hud", "../assets/images/hud2.png");
    assetStore->AddFont("charriot-font", "../assets/fonts/charriot.ttf", 24);
    assetStore->AddTexture(renderer, "tilemap-image", mapImagePath);
    assetStore->AddTexture(renderer, "tank-image", "../assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "../assets/images/truck-ford-right.png");
    assetStore->AddTexture(renderer, "chopper-image", "../assets/images/chopper.png");
    assetStore->AddTexture(renderer, "player-idle-image", "../assets/sprites/CharacterIdle.png");
    assetStore->AddTexture(renderer, "bullet-image", "../assets/images/bullet.png");

    Entity player = registry->CreateEntity();
    player.Tag("player");
    player.AddComponent<TransformComponent>(glm::vec2(256, 256), glm::vec2(2.0, 2.0), 0.0);
    player.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    player.AddComponent<SpriteComponent>("player-idle-image", 32, 32, 1, false, false);
    player.AddComponent<AnimationComponent>(6, 8, true);
//    player.AddComponent<CameraFollowComponent>();
    player.AddComponent<BoxColliderComponent>(32, 32);
    player.AddComponent<PlayerControllerComponent>(glm::vec2(0, -80.0), glm::vec2(80.0, 0), glm::vec2(0, 80.0), glm::vec2(-80.0, 0));
    player.AddComponent<HealthComponent>(100);
    player.AddComponent<RaycastComponent>(glm::vec2(256, 256));
//    player.AddComponent<StateMachineComponent>("idle");
//    player.AddComponent<ProjectileEmitterComponent>(glm::vec2(150, 0), 1000, 1000, 10, false);

//    Entity tank = registry->CreateEntity();
//    tank.AddComponent<TransformComponent>(glm::vec2(0.0, 100.0), glm::vec2(2.0, 2.0), 0.0);
//    tank.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
//    tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 1, false, 0, 0);
//    tank.AddComponent<BoxColliderComponent>(32-10, 32-10, glm::vec2(10,10));
//    tank.AddComponent<ProjectileEmitterComponent>(glm::vec2(150, 0), 1000, 1000, 10, false);

//    Entity label = registry->CreateEntity();
//    SDL_Color red = {255,0,0};
//    label.AddComponent<TextLabelComponent>(glm::vec2(200, 200), "This is a label", "charriot-font", red, true);
}


/**
 * UpdateSystems
 */
void Game::UpdateSystems()
{
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks64() - millisecsPreviouseFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // The difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - millisecsPreviouseFrame) / 1000.0;

    millisecsPreviouseFrame = SDL_GetTicks();

    // Reset all event handlers for the current frame
    eventBus->Reset();

    // Perform the subscription of the events for all systems
    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<PlayerControlSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventBus);

    // UpdateSystems the registry to process the entities that are waiting to be created/deleted
    registry->Update();

    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update(eventBus);
    registry->GetSystem<CameraMovementSystem>().Update(camera);
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();
};


/**
 * Renderer update
 */
void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render
    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
    registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore, camera);

    if (isDebug) {
        registry->GetSystem<RenderColliderSystem>().Update(renderer, camera);
        auto player = registry->GetEntityByTag("player");
        registry->GetSystem<RenderRaycastSystem>().Update(renderer, player);
    }
    
    if (isImGui) {
        registry->GetSystem<RenderImGuiSystem>().Update(registry, camera);
    }

    // Display HUD
    SDL_Texture* hud = assetStore->GetTexture("hud");
    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = 640;
    source.h = 64;

    SDL_Rect destination;
    destination.x = 0;
    destination.y = 480-64;
    destination.w = 640;
    destination.h = 64;

    SDL_RenderCopy(renderer, hud, &source, &destination);

    SDL_RenderPresent(renderer);
}


/**
 * Housekeeping
 */
void Game::Destroy()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};


/**
 * Game loop
 */
void Game::Run()
{
    SetUpGameObjects();

     while (isRunning)
     {
         ProcessInput();
         UpdateSystems();
         Render();
     }
}


