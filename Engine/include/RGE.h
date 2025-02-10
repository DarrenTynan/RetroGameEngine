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

/**
 * @brief definition pf the class functions.
 */
class RGE
{
public:
    static void InitialSetup();
    static void SetupGameSDL();
    static void UpdateRenderer();
    static bool ProcessDebugInputEvents();
    static void UpdateSystems();
    static void LoadLevel();
    static void SetupTMX();
    static void destroy();

private:

    static void DrawGrid();
};

#endif //RETROGAMEENGINE_RGE_H
