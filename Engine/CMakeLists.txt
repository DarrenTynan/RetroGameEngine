cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(RGE)

SET( RGE_DIR "${PROJECT_SOURCE_DIR}/src" )

add_library(RGE STATIC
        ${RGE_DIR}/AssetStore/include/AssetStore.h
        ${RGE_DIR}/AssetStore/AssetStore.cpp

        ${RGE_DIR}/Components/include/AnimationComponent.h
        ${RGE_DIR}/Components/include/BoxColliderComponent.h
        ${RGE_DIR}/Components/include/CameraFollowComponent.h
        ${RGE_DIR}/Components/include/HealthComponent.h
        ${RGE_DIR}/Components/include/PlayerControllerComponent.h
        ${RGE_DIR}/Components/include/ProjectileComponent.h
        ${RGE_DIR}/Components/include/ProjectileEmitterComponent.h
        ${RGE_DIR}/Components/include/RayCastComponent.h
        ${RGE_DIR}/Components/include/RigidBodyComponent.h
        ${RGE_DIR}/Components/include/ScriptComponent.h
        ${RGE_DIR}/Components/include/TextLabelComponent.h
        ${RGE_DIR}/Components/include/TransformComponent.h

        ${RGE_DIR}/ECS/include/Component.h
        ${RGE_DIR}/ECS/include/ECS.h
        ${RGE_DIR}/ECS/include/Entity.h
        ${RGE_DIR}/ECS/include/Pool.h
        ${RGE_DIR}/ECS/include/Registry.h
        ${RGE_DIR}/ECS/ECS.cpp

        ${RGE_DIR}/EventBus/include/Event.h
        ${RGE_DIR}/EventBus/include/EventBus.h

        ${RGE_DIR}/Events/include/CollisionEvent.h
        ${RGE_DIR}/Events/include/KeyPressedEvent.h
        ${RGE_DIR}/Events/include/KeyReleasedEvent.h

        ${RGE_DIR}/FSM/include/BaseState.h
        ${RGE_DIR}/FSM/include/FSM.h
        ${RGE_DIR}/FSM/include/States.h
        ${RGE_DIR}/FSM/FSM.cpp
        ${RGE_DIR}/FSM/StateTransitions.cpp

        ${RGE_DIR}/LevelLoader/include/LevelLoader.h
        ${RGE_DIR}/LevelLoader/LevelLoader.cpp

        ${RGE_DIR}/Systems/include/AnimationSystem.h
        ${RGE_DIR}/Systems/include/CameraMovementSystem.h
        ${RGE_DIR}/Systems/include/CollisionSystem.h
        ${RGE_DIR}/Systems/include/DamageSystem.h
        ${RGE_DIR}/Systems/include/MovementSystem.h
        ${RGE_DIR}/Systems/include/PlayerMovementSystem.h
        ${RGE_DIR}/Systems/include/ProjectileEmitSystem.h
        ${RGE_DIR}/Systems/include/ProjectileLifecycleSystem.h
        ${RGE_DIR}/Systems/include/RenderColliderSystem.h
        ${RGE_DIR}/Systems/include/RenderHealthBarSystem.h
        ${RGE_DIR}/Systems/include/RenderRayCastSystem.h
        ${RGE_DIR}/Systems/include/RenderSystem.h
        ${RGE_DIR}/Systems/include/RenderTextSystem.h
        ${RGE_DIR}/Systems/include/ScriptSystem.h

        ${RGE_DIR}/RGE.cpp


)

link_directories( /usr/local/lib )
include_directories( /usr/local/include )

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( SDL2_TTF REQUIRED )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
