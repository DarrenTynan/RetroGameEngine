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

#include "../../Engine/src/Logger/Logger.h"
#include "../../Engine/src/ECS/include/ECS.h"
#include "../../Engine/src/AssetStore/AssetStore.h"
#include "../../Engine/src/EventBus/EventBus.h"
//#include "../../Engine/src/LevelLoader/LevelLoader.h"
#include "../../Engine/src/FSM/include/FSM.h"

#include "../../Engine/src/Components/TransformComponent.h"
#include "../../Engine/src/Components/RigidBodyComponent.h"
#include "../../Engine/src/Components/SpriteComponent.h"
#include "../../Engine/src/Components/CameraFollowComponent.h"
#include "../../Engine/src/Components/TextLabelComponent.h"
#include "../../Engine/src/Components/AnimationComponent.h"
#include "../../Engine/src/Components/BoxColliderComponent.h"
#include "../../Engine/src/Components/ProjectileComponent.h"
#include "../../Engine/src/Components/ProjectileEmitterComponent.h"
#include "../../Engine/src/Components/HealthComponent.h"
#include "../../Engine/src/Components/RaycastComponent.h"
#include "../../Engine/src/Components/PlayerControlComponent.h"
#include "../../Engine/src/Components/CameraFollowComponent.h"
                
#include "../../Engine/src/Systems/CameraMovementSystem.h"
#include "../../Engine/src/Systems/PlayerMovementSystem.h"
#include "../../Engine/src/Systems/MovementSystem.h"
#include "../../Engine/src/Systems/RenderSystem.h"
#include "../../Engine/src/Systems/RenderTextSystem.h"
#include "../../Engine/src/Systems/RenderColliderSystem.h"
#include "../../Engine/src/Systems/AnimationSystem.h"
#include "../../Engine/src/Systems/CollisionSystem.h"
#include "../../Engine/src/Systems/RenderImGuiSystem.h"
#include "../../Engine/src/Systems/ProjectileEmitSystem.h"
#include "../../Engine/src/Systems/ProjectileLifecycleSystem.h"
#include "../../Engine/src/Systems/DamageSystem.h"
#include "../../Engine/src/Systems/RenderRaycastSystem.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/Property.hpp>

//#include "../../Engine/libs/tmxlite/Map.hpp"
//#include "../../Engine/libs/tmxlite/Layer.hpp"
//#include "../../Engine/libs/tmxlite/TileLayer.hpp"
//#include "../../Engine/libs/tmxlite/Tileset.hpp"
//#include "../../Engine/libs/tmxlite/ObjectGroup.hpp"
//#include "../../Engine/libs/tmxlite/Property.hpp"

/**
 * @brief definition pf the class functions.
 */
class RGE
{
public:
    static void InitialSetup();
    static void SetupRgeSDL();
    static void SetupGameSDL();
    static void UpdateRenderer();
    static bool ProcessDebugInputEvents();
    static void UpdateSystems();
    static void SetupImGui();
    static void LoadLevel();
    static void SetupTMX();
    static void destroy();

private:

    static void DrawGrid();
};

#endif //RETROGAMEENGINE_RGE_H
