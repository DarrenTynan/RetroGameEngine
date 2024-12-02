//
// Created by Darren Tynan on 17/11/2024.
//

#ifndef RETROGAMEENGINE_RGE_H
#define RETROGAMEENGINE_RGE_H

#include <iostream>
#include <stdio.h>
#include <string>

#include <glm/glm.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include "../../RGE/src/Logger/Logger.h"
#include "../../RGE/src/ECS/ECS.h"
#include "../../RGE/src/AssetStore/AssetStore.h"
#include "../../RGE/src/EventBus/EventBus.h"

#include "../../RGE/src/Components/TransformComponent.h"
#include "../../RGE/src/Components/RigidBodyComponent.h"
#include "../../RGE/src/Components/SpriteComponent.h"
#include "../../RGE/src/Components/CameraFollowComponent.h"
#include "../../RGE/src/Components/TextLabelComponent.h"
#include "../../RGE/src/Components/AnimationComponent.h"
#include "../../RGE/src/Components/BoxColliderComponent.h"
#include "../../RGE/src/Components/PlayerControllerComponent.h"
//#include "../../RGE/src/Components/StateMachineComponent.h"
#include "../../RGE/src/Components/ProjectileComponent.h"
#include "../../RGE/src/Components/ProjectileEmitterComponent.h"
#include "../../RGE/src/Components/HealthComponent.h"
#include "../../RGE/src/Components/RaycastComponent.h"

#include "../../RGE/src/Systems/CameraMovementSystem.h"
#include "../../RGE/src/Systems/MovementSystem.h"
#include "../../RGE/src/Systems/RenderSystem.h"
#include "../../RGE/src/Systems/RenderTextSystem.h"
#include "../../RGE/src/Systems/RenderColliderSystem.h"
#include "../../RGE/src/Systems/AnimationSystem.h"
#include "../../RGE/src/Systems/CollisionSystem.h"
#include "../../RGE/src/Systems/PlayerControlSystem.h"
#include "../../RGE/src/Systems/RenderImGuiSystem.h"
//#include "../../RGE/src/Systems/StateMachineSystem.h"
#include "../../RGE/src/Systems/ProjectileEmitSystem.h"
#include "../../RGE/src/Systems/ProjectileLifecycleSystem.h"
#include "../../RGE/src/Systems/DamageSystem.h"
#include "../../RGE/src/Systems/RenderRaycastSystem.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/Property.hpp>

// Global vars
static const int FPS = 60;
static const int MILLISECS_PER_FRAME = 1000 / FPS;
static ImVec4 game_clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
static ImVec4 rge_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static std::unique_ptr<Registry> registry;
static std::unique_ptr<AssetStore> assetStore;
static std::unique_ptr<EventBus> eventBus;

static bool isRunning = false;
static bool isCollider = false;
static bool isRayCast = false;
static bool isFullScreen = false;

static bool testBool = true;

static SDL_Rect rgeCamera;
static SDL_Rect gameCamera;
static SDL_Window* rgeWindow;
static SDL_Renderer* rgeRenderer;
const static int GAME_WINDOW_WIDTH = 800;
const static int GAME_WINDOW_HEIGHT = 600;

static SDL_Window* gameWindow;
static SDL_Renderer* gameRenderer;

static const auto MAP_PATH = "../Game/assets/tilemaps/TestLevel/TestLevel.tmx";
//const auto MAP_PATH = "../Game/assets/tilemaps/Level_01.tmx";
static std::string mapImagePath;
static tmx::Map map;

static int millisecsPreviouseFrame = 0;
static int windowWidth{};
static int windowHeight{};
static int mapWidth{};
static int mapHeight{};


class RGE
{
public:
    static void setupVars();
    static void sayHello();
    static int setupSDL();
    static int setupRgeSDL();
    static int setupGameSDL();
    static void setupImGui();
    static void render();
    static void setupRegistry();
    static void setupAssets();
    static void setupObjects();
    static int setupTMX();
    static bool processInput();
    static void updateSystems();
    static void destroy();

private:

};

#endif //RETROGAMEENGINE_RGE_H
