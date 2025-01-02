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
#include "../../RGE/src/ECS/include/ECS.h"
#include "../../RGE/src/AssetStore/AssetStore.h"
#include "../../RGE/src/EventBus/EventBus.h"
//#include "../../RGE/src/LevelLoader/LevelLoader.h"
#include "../../RGE/src/FSM/include/FSM.h"

#include "../../RGE/src/Components/TransformComponent.h"
#include "../../RGE/src/Components/RigidBodyComponent.h"
#include "../../RGE/src/Components/SpriteComponent.h"
#include "../../RGE/src/Components/CameraFollowComponent.h"
#include "../../RGE/src/Components/TextLabelComponent.h"
#include "../../RGE/src/Components/AnimationComponent.h"
#include "../../RGE/src/Components/BoxColliderComponent.h"
#include "../../RGE/src/Components/ProjectileComponent.h"
#include "../../RGE/src/Components/ProjectileEmitterComponent.h"
#include "../../RGE/src/Components/HealthComponent.h"
#include "../../RGE/src/Components/RaycastComponent.h"
#include "../../RGE/src/Components/PlayerControlComponent.h"
#include "../../RGE/src/Components/CameraFollowComponent.h"

#include "../../RGE/src/Systems/CameraMovementSystem.h"
#include "../../RGE/src/Systems/PlayerMovementSystem.h"
#include "../../RGE/src/Systems/MovementSystem.h"
#include "../../RGE/src/Systems/RenderSystem.h"
#include "../../RGE/src/Systems/RenderTextSystem.h"
#include "../../RGE/src/Systems/RenderColliderSystem.h"
#include "../../RGE/src/Systems/AnimationSystem.h"
#include "../../RGE/src/Systems/CollisionSystem.h"
#include "../../RGE/src/Systems/RenderImGuiSystem.h"
#include "../../RGE/src/Systems/ProjectileEmitSystem.h"
#include "../../RGE/src/Systems/ProjectileLifecycleSystem.h"
#include "../../RGE/src/Systems/DamageSystem.h"
#include "../../RGE/src/Systems/RenderRaycastSystem.h"

// Linker errors if ScriptSystem.h included
//#include "../../RGE/src/Systems/ScriptSystem.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/Property.hpp>


/**
 * @brief definition pf the class functions.
 */
class RGE
{
public:
    static void setupVars();
    static int setupSDL();
    static int setupRgeSDL();
    static int setupGameSDL();
    static void setupImGui();
    static void updateRenderer();
    static void setupSystemRegistry();
    static void setupAssets();
    static void setupObjects();
    static int setupTMX();
    static bool processDebugInputEvents();
    static void updateSystems();
    static void destroy();

private:

    static void drawGrid();
};

#endif //RETROGAMEENGINE_RGE_H
