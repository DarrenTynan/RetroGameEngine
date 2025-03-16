//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/RGE.h"

#include "Systems/include/ScriptSystem.h"
#include "LevelLoader/include/LevelLoader.h"

#include <glm/glm.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "../../Engine/src/ECS/include/ECS.h"
#include "../src/AssetStore/include/AssetStore.h"
#include "../src/EventBus/include/EventBus.h"
//#include "../../Engine/src/LevelLoader/LevelLoader.h"
#include "../../Engine/src/FSM/include/FSM.h"

#include "../src/Components/include/TransformComponent.h"
#include "../src/Components/include/RigidBodyComponent.h"
#include "../src/Components/include/SpriteComponent.h"
#include "../src/Components/include/CameraFollowComponent.h"
#include "../src/Components/include/TextLabelComponent.h"
#include "../src/Components/include/AnimationComponent.h"
#include "../src/Components/include/BoxColliderComponent.h"
#include "../src/Components/include/ProjectileComponent.h"
#include "../src/Components/include/ProjectileEmitterComponent.h"
#include "../src/Components/include/HealthComponent.h"
#include "../src/Components/include/RaycastComponent.h"
#include "../src/Systems/include/InputControlSystem.h"
#include "../src/Components/include/CameraFollowComponent.h"

#include "../src/Systems/include/CameraMovementSystem.h"
#include "../src/Systems/include/PlayerControllerSystem.h"
#include "../src/Systems/include/MovementSystem.h"
#include "../src/Systems/include/RenderSystem.h"
#include "../src/Systems/include/RenderTextSystem.h"
#include "../src/Systems/include/RenderColliderSystem.h"
#include "../src/Systems/include/AnimationSystem.h"
#include "../src/Systems/include/CollisionSystem.h"

#include "../src/Systems/include/ProjectileEmitSystem.h"
#include "../src/Systems/include/ProjectileLifecycleSystem.h"
#include "../src/Systems/include/DamageSystem.h"
#include "../src/Systems/include/RenderRaycastSystem.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/Property.hpp>

using namespace RGE_ECS;
using namespace RGE_Component;
using namespace RGE_AssetStore;
using namespace RGE_EventBus;
using namespace RGE_Events;

SDL_Window* gameWindow;
SDL_Rect gameCamera;
SDL_Renderer* gameRenderer;

std::shared_ptr<Registry> registry = std::make_shared<Registry>();
std::unique_ptr<AssetStore> assetStore = std::make_unique<AssetStore>();
std::unique_ptr<EventBus> eventBus = std::make_unique<EventBus>();

std::string gameWindowTitle = "Default Game_Engine Title";
const int gameWindowWidth = 800;
const int gameWindowHeight = 600;

// Debug keyboard toggles
bool isCollider = false;
bool isRayCast = false;
bool isCamera = true;

int g_millisecsPreviouseFrame = 0;

// Lua
sol::state lua;
//LevelLoader levelLoader;

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif


/**
 * @brief Initialise the registry with systems. Set up the Lua level loader system.
 */
void RGE::InitialSetup()
{
    std::cout << "Library Test Call From InitialSetup\n";

    // Add the systems that need to be processed in our game
    registry->AddSystem<InputControlSystem>();            // Read keys and control player movements.
    registry->AddSystem<MovementSystem>();                // Move all entities
    registry->AddSystem<PlayerControllerSystem>();        // Move the player & apply forces
    registry->AddSystem<AnimationSystem>();               // Animate all entities
    registry->AddSystem<CollisionSystem>();               // Check all entity collisions AABB
    registry->AddSystem<DamageSystem>();                  // Check all damage systems
    registry->AddSystem<CameraMovementSystem>();          // Check the camera move system
    registry->AddSystem<ProjectileEmitSystem>();          // Check entity bullets AABB
    registry->AddSystem<ProjectileLifecycleSystem>();     // Check the life cycle and kill off bullets
    registry->AddSystem<RenderColliderSystem>();          // Debug updateRender collision box's
    registry->AddSystem<RenderSystem>();                  // Render windows
    registry->AddSystem<RenderTextSystem>();              // Render any label's
    registry->AddSystem<RenderRaycastSystem>();           // Debug updateRender the ray cast's
    registry->AddSystem<ScriptSystem>();                  // Lua scripting system

    // Create the bindings between C++ and Lua
    registry->GetSystem<ScriptSystem>().CreateLuaBindings(lua);

    // Use all the libraries
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);

    // Load config file
    LevelLoader::LoadConfig(lua);

    // Setup SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL could not be initialised\n" << SDL_GetError();
        exit(1);
    }

    // Setup true type fonts
    if (TTF_Init() != 0)
    {
        exit(1);
    }

    // From 2.0.18: Enable native IME.
    #ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

}


/**
 * @brief Setup game SDL window, renderer and camera
 *
 * @return -1 for errors
 */
void RGE::SetupGameSDL()
{
    // Create window with SDL_Renderer graphics context
    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    gameWindow = SDL_CreateWindow(
            "Game_Engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            gameWindowWidth,
            gameWindowHeight,
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
    gameCamera = {0, 0, gameWindowWidth, gameWindowHeight };

}


/**
  * @brief Initialise the assetStore with pointers to png.
 */
void RGE::LoadLevel()
{
    // Load the entity data for level 1
    LevelLoader::LoadLevel(lua, registry, assetStore, gameRenderer, 1);

}


void RGE::DrawGrid()
{
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
    for (int i = 0; i < gameWindowHeight; ++i)
    {
        SDL_RenderDrawLine(gameRenderer, 0, i * 32, gameWindowWidth, i * 32);
    }
    for (int i = 0; i < gameWindowWidth; ++i)
    {
        SDL_RenderDrawLine(gameRenderer, i * 32, 0, i * 32, gameWindowWidth);
    }
    SDL_RenderPresent(gameRenderer);
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
        auto player = registry->GetEntityByTag("player");
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

    // Display HUD
    SDL_Texture* hud = assetStore->GetTexture("hud2");
    SDL_Rect source = {0,0,800, 56};
    SDL_Rect destination = {0,600-56,800,56};

    SDL_RenderCopy(gameRenderer, hud, &source, &destination);
    SDL_RenderPresent(gameRenderer);

}


/**
 * Load the tmx map files and iterate over.
 *
 * @return
 */
void RGE::SetupTMX()
{
    tmx::Map map;
    const auto MAP_PATH = "../Game_Engine/assets/tilemaps/TestLevel/TestLevel.tmx";
    std::string mapImagePath;
    int mapWidth;
    int mapHeight;

    if(map.load(MAP_PATH))
    {
        const auto& layers = map.getLayers();
        for(const auto& layer : layers)
        {
            // Get Object layer
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
                    tile.AddTag("object");

                }
            }
                // Get Tile layer
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
                        tile.AddTag("tile");

                        tile.AddComponent<TransformComponent>(glm::vec2(x * tileWidth, y * tileHeight), glm::vec2(1, 1), 0.0);
                        tile.AddComponent<SpriteComponent>("tilemap-image", tileWidth, tileHeight, 0, true, false, srcRectX, srcRectY);
                        index++;
                    }
                }
            }
        }

//        const auto& tilesets = map.getTilesets();
//        for(const auto& tileset : tilesets)
//        {
//            Logger::Log(tileset.getImagePath());
//            read out tile set properties, load textures etc...
//        }
    }

}


/**
 * Poll window events:
 *
 * window quit
 * keyboard
 */
bool RGE::ProcessDebugInputEvents()
{
    bool isQuit = true;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        if (sdlEvent.type == SDL_KEYUP)
        {
            eventBus->EmitEvent<KeyReleasedEvent>(sdlEvent.key.keysym.sym);
        }

        if (sdlEvent.type == SDL_KEYDOWN)
        {
            eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
        }

        // Core sdl events.
        switch (sdlEvent.type)
        {
            // Window close
            case SDL_QUIT:
                isQuit = false;
                break;

            // Check for window event
            case SDL_WINDOWEVENT:

                switch (sdlEvent.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        isQuit = false;
                        break;
                }
                break;

            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { isQuit = false; }
                if (sdlEvent.key.keysym.sym == SDLK_c) { isCollider = !isCollider; }
                if (sdlEvent.key.keysym.sym == SDLK_r) { isRayCast = !isRayCast; }

                // Up
                if (sdlEvent.key.keysym.sym == SDLK_UP)
                {
                    eventBus->EmitEvent<WalkUpEvent>(sdlEvent.key.keysym.sym);
                }

                // Down
                if (sdlEvent.key.keysym.sym == SDLK_DOWN)
                {
                    eventBus->EmitEvent<WalkDownEvent>(sdlEvent.key.keysym.sym);
                }

                // Left
                if (sdlEvent.key.keysym.sym == SDLK_LEFT)
                {
                    eventBus->EmitEvent<WalkLeftEvent>(sdlEvent.key.keysym.sym);
                }

                // Right
                if (sdlEvent.key.keysym.sym == SDLK_RIGHT)
                {
                    eventBus->EmitEvent<WalkRightEvent>(sdlEvent.key.keysym.sym);
                }

                if (sdlEvent.key.keysym.sym == SDLK_SPACE)
                {
                    eventBus->EmitEvent<JumpEvent>(sdlEvent.key.keysym.sym);
                }

        }
    };
    return isQuit;
};


/**
 * UpdateSystems
 */
void RGE::UpdateSystems()
{
    // The difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - g_millisecsPreviouseFrame) / 1000.0;

    // Store the "previous" frame time
    g_millisecsPreviouseFrame = SDL_GetTicks();

    // Reset all event handlers for the current frame
    eventBus->Reset();

    // Perform the subscription of the events for all systems
    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);

    registry->GetSystem<InputControlSystem>().SubscribeToEvents(eventBus, registry);
    registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventBus);

    // UpdateSystems the registry to process the entities that are waiting to be created/deleted
    registry->Update();

    registry->GetSystem<MovementSystem>().Update(deltaTime);                            // apply velocityDelta and check out of bounds.
    registry->GetSystem<PlayerControllerSystem>().Update(registry, deltaTime);        // apply velocityDelta and check out of bounds.
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update(eventBus);

    registry->GetSystem<CameraMovementSystem>().Update(gameRenderer, gameCamera);

    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();

}


/**
 * Destroy
 */
void RGE::destroy()
{
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);

    SDL_Quit();
}

