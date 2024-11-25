//
// Created by Darren Tynan on 17/11/2024.
//

#ifndef RETROGAMEENGINE_GAME_H
#define RETROGAMEENGINE_GAME_H

#include <iostream>
#include <stdio.h>

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
//#include "../Components/StateMachineComponent.h"
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
//#include "../Systems//StateMachineSystem.h"
#include "../../RGE/src/Systems/ProjectileEmitSystem.h"
#include "../../RGE/src/Systems/ProjectileLifecycleSystem.h"
#include "../../RGE/src/Systems/DamageSystem.h"
#include "../../RGE/src/Systems/RenderRaycastSystem.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/ObjectGroup.hpp>

//int windowWidth;
//int windowHeight;
//int mapWidth;
//int mapHeight;

// Global vars
const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Surface* windowSurface = nullptr;
        SDL_Rect camera;

        bool isRunning = false;
        bool isDebug = false;
        bool isImGui = false;
        bool isFullScreen = false;

        int millisecsPreviouseFrame = 0;
        int windowWidth = 640;
        int windowHeight = 480;
        int mapWidth;
        int mapHeight;

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        std::unique_ptr<Registry> registry;
        std::unique_ptr<AssetStore> assetStore;
        std::unique_ptr<EventBus> eventBus;

public:
        Game();
        virtual ~Game();

        int Initialize();

        void Run();
        int GetTMX();
        void SetUpGameObjects();
        void ProcessInput();
        void UpdateSystems();
        void Render();
        void RenderImGui();
        void Destroy();
        void RenderTree();
};

#endif //RETROGAMEENGINE_GAME_H
