//
// Created by Darren Tynan on 17/11/2024.
//

#include <filesystem>

#include "../include/RGE.h"

#include "Systems/include/ScriptSystem.h"
#include "LevelLoader/include/LevelLoader.h"

#include <glm/glm.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../src/EventBus/include/EventBus.h"
#include "../src/Components/include/SpriteComponent.h"
#include "../src/Components/include/BoxColliderComponent.h"
#include "../src/Components/include/TextLabelComponent.h"
#include "../src/Systems/include/PlayerControllerSystem.h"
#include "../src/Systems/include/CameraMovementSystem.h"
//#include "../src/Systems/include/EntityMovementSystem.h"
#include "../src/Systems/include/RenderSystem.h"
#include "../src/Systems/include/RenderTextSystem.h"
#include "../src/Systems/include/RenderColliderSystem.h"
#include "../src/Systems/include/AnimationSystem.h"
#include "../src/Systems/include/PlayerCollisionSystem.h"
//#include "../src/Systems/include/EntityCollisionSystem.h"
#include "../src/Systems/include/ProjectileEmitSystem.h"
#include "../src/Systems/include/ProjectileLifecycleSystem.h"
#include "../src/Systems/include/DamageSystem.h"
#include "../src/Systems/include/RenderRaycastSystem.h"
#include "FileHandler/include/FileHandler.h"

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
using namespace RGE_FILEHANDLER;

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
bool isPlayer = false;

uint32_t msSincePreviousFrame = 0;

// Lua
sol::state lua;
//LevelLoader levelLoader;

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

    // Create a Document object to hold the JSON data
    rapidjson::Document jsonDoc;

    // Parse the JSON data
    jsonDoc.Parse(json.c_str());

    // Check for parse errors
    if (jsonDoc.HasParseError())
    {
        std::cerr << "Error parsing JSON: " << jsonDoc.GetParseError() << std::endl;
        exit(1);
    }

    // Add the systems that need to be processed in our game
//    registry->AddSystem<EntityMovementSystem>();          // Move all entities
    registry->AddSystem<PlayerControllerSystem>();        // Move the player & apply forces
    registry->AddSystem<AnimationSystem>();               // Animate all entities
    registry->AddSystem<PlayerCollisionSystem>();         // Check all entity collisions AABB
//    registry->AddSystem<EntityCollisionSystem>();         // Check all entity collisions AABB
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
            jsonDoc["configuration"]["window_title"].GetString(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            jsonDoc["configuration"]["window_width"].GetInt(),
            jsonDoc["configuration"]["window_height"].GetInt(),
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
    gameCamera = {0, 0, jsonDoc["configuration"]["window_width"].GetInt(), jsonDoc["configuration"]["window_height"].GetInt() };

}


/**
  * @brief Initialise the assetStore with pointers to png.
 */
void RGE::LoadLevel()
{
    // Load the entity data for level 1
    LevelLoader::LoadLevel(lua, registry, assetStore, gameRenderer, 1);
//    std::cout << 'lua["level"]["tilemap"]' << std::endl;
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

//    if (isRayCast)
//    {
//        auto player = registry->GetEntityByTag("player");
//        registry->GetSystem<RenderRaycastSystem>().Update(gameRenderer, player);
//    }

//    if (isPlayer)
//    {
//        auto player = registry->GetEntityByTag("player");
//        auto transform = player.GetComponent<TransformComponent>();
//        transform.position.x = 32.0;
//        transform.position.y = 32.0;
//    }

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
                if (sdlEvent.key.keysym.sym == SDLK_p) { isPlayer = !isPlayer; }

            break;
        }
    };
    return isQuit;
};


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
    registry->GetSystem<PlayerControllerSystem>().Update(deltaTime);

    /**
     * @brief AABB collision player to all other objects.
     */
//    registry->GetSystem<PlayerCollisionSystem>().Update(eventBus, registry);
//    registry->GetSystem<EntityCollisionSystem>().Update(eventBus);

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

    SDL_Quit();
}

