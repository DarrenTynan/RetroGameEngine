#
# Retro Game Engine: Engine static library
#
cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 17)

project(RGE_Engine VERSION 1)

SET( SRC_DIR        "${PROJECT_SOURCE_DIR}/src" )
SET( LIBS_DIR       "${PROJECT_SOURCE_DIR}/libs" )
SET( LUA_DIR        "${LIBS_DIR}/lua" )
SET( SOL2_DIR       "${LIBS_DIR}/sol" )

message("My SRC_DIR directory: ${SRC_DIR}")
message("My LIBS_DIR directory: ${LIBS_DIR}")
message("My LUA_DIR directory: ${LUA_DIR}")
message("My SOL2_DIR directory: ${SOL2_DIR}")
message("My project name: ${PROJECT_NAME}")

#
# Build lua library
#
add_library(lua STATIC
        ${LUA_DIR}/lapi.c
        ${LUA_DIR}/lauxlib.c
        ${LUA_DIR}/lbaselib.c
        ${LUA_DIR}/lcode.c
        ${LUA_DIR}/lcorolib.c
        ${LUA_DIR}/lctype.c
        ${LUA_DIR}/ldblib.c
        ${LUA_DIR}/ldebug.c
        ${LUA_DIR}/ldo.c
        ${LUA_DIR}/ldump.c
        ${LUA_DIR}/lfunc.c
        ${LUA_DIR}/lgc.c
        ${LUA_DIR}/linit.c
        ${LUA_DIR}/liolib.c
        ${LUA_DIR}/llex.c
        ${LUA_DIR}/lmathlib.c
        ${LUA_DIR}/lmem.c
        ${LUA_DIR}/loadlib.c
        ${LUA_DIR}/lobject.c
        ${LUA_DIR}/lopcodes.c
        ${LUA_DIR}/loslib.c
        ${LUA_DIR}/lparser.c
        ${LUA_DIR}/lstate.c
        ${LUA_DIR}/lstring.c
        ${LUA_DIR}/lstrlib.c
        ${LUA_DIR}/ltable.c
        ${LUA_DIR}/ltablib.c
        ${LUA_DIR}/ltm.c
        ${LUA_DIR}/lua.c
        ${LUA_DIR}/lundump.c
        ${LUA_DIR}/lutf8lib.c
        ${LUA_DIR}/lvm.c
        ${LUA_DIR}/lzio.c
)

#
# Build the RGE static library
#
add_library(RGE_Engine STATIC
        ${SRC_DIR}/AssetStore/include/AssetStore.h
        ${SRC_DIR}/AssetStore/src/AssetStore.cpp

        ${SRC_DIR}/Components/include/AnimationComponent.h
        ${SRC_DIR}/Components/include/BoxColliderComponent.h
        ${SRC_DIR}/Components/include/CameraFollowComponent.h
        ${SRC_DIR}/Components/include/HealthComponent.h
        ${SRC_DIR}/Components/include/ProjectileComponent.h
        ${SRC_DIR}/Components/include/ProjectileEmitterComponent.h
        ${SRC_DIR}/Components/include/RayCastComponent.h
        ${SRC_DIR}/Components/include/RigidBodyComponent.h
        ${SRC_DIR}/Components/include/ScriptComponent.h
        ${SRC_DIR}/Components/include/SpriteComponent.h
        ${SRC_DIR}/Components/include/TextLabelComponent.h
        ${SRC_DIR}/Components/include/TransformComponent.h
        ${SRC_DIR}/Components/include/SpritesheetComponent.h

        ${SRC_DIR}/ECS/include/Pool.h
        ${SRC_DIR}/ECS/include/Component.h
        ${SRC_DIR}/ECS/include/Entity.h
        ${SRC_DIR}/ECS/include/ECS.h
        ${SRC_DIR}/ECS/include/System.h
        ${SRC_DIR}/ECS/include/Registry.h
        ${SRC_DIR}/ECS/ECS.cpp

        ${SRC_DIR}/EventBus/include/Event.h
        ${SRC_DIR}/EventBus/include/EventBus.h

        ${SRC_DIR}/Events/include/CollisionEvent.h

        ${SRC_DIR}/FSM/include/BaseState.h
        ${SRC_DIR}/FSM/include/FSM.h
        ${SRC_DIR}/FSM/include/States.h
        ${SRC_DIR}/FSM/FSM.cpp
        ${SRC_DIR}/FSM/StateTransitions.cpp

        ${SRC_DIR}/LevelLoader/include/LevelLoader.h
        ${SRC_DIR}/LevelLoader/LevelLoader.cpp

        ${SRC_DIR}/Systems/include/AnimationSystem.h
        ${SRC_DIR}/Systems/include/CameraFollowSystem.h
        ${SRC_DIR}/Systems/include/PlayerCollisionSystem.h
        ${SRC_DIR}/Systems/include/EntityCollisionSystem.h
        ${SRC_DIR}/Systems/include/DamageSystem.h
        ${SRC_DIR}/Systems/include/EntityMovementSystem.h
        ${SRC_DIR}/Systems/include/PlayerControllerSystem.h
        ${SRC_DIR}/Systems/include/ProjectileEmitSystem.h
        ${SRC_DIR}/Systems/include/ProjectileLifecycleSystem.h
        ${SRC_DIR}/Systems/include/RenderColliderSystem.h
        ${SRC_DIR}/Systems/include/RenderHealthBarSystem.h
        ${SRC_DIR}/Systems/include/RenderRayCastSystem.h
        ${SRC_DIR}/Systems/include/RenderSystem.h
        ${SRC_DIR}/Systems/include/RenderTextSystem.h
        ${SRC_DIR}/Systems/include/EditorSystem.h

        ${SRC_DIR}/FileHandler/include/FileHandler.h
        ${SRC_DIR}/FileHandler/FileHandler.cpp
        ${SRC_DIR}/Components/include/FSMComponent.h
        ${SRC_DIR}/Components/include/SpritesheetComponent.h

        ${SOL2_DIR}/sol.hpp

        ${SRC_DIR}/RGE.cpp

        ${SOL2_DIR}/config.hpp
        ${SOL2_DIR}/forward.hpp
        ${SOL2_DIR}/sol.hpp
)

link_directories( /usr/local/lib )

include_directories(
        /usr/local/include
        ${LUA_INCLUDE_DIR}
)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/libs/lua/
        ${PROJECT_SOURCE_DIR}/libs/sol/
        ${PROJECT_SOURCE_DIR}/AssetStore/
        ${PROJECT_SOURCE_DIR}/Components/
        ${PROJECT_SOURCE_DIR}/ECS/
        ${PROJECT_SOURCE_DIR}/EventBus/
        ${PROJECT_SOURCE_DIR}/Events/
        ${PROJECT_SOURCE_DIR}/FileHandler/
        ${PROJECT_SOURCE_DIR}/FSM/
        ${PROJECT_SOURCE_DIR}/LevelLoader/
        ${PROJECT_SOURCE_DIR}/Systems/
)

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( SDL2_TTF REQUIRED )
find_package( GLM REQUIRED )
find_package( Lua REQUIRED )
find_package(nlohmann_json 3.11.3 REQUIRED)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

target_link_libraries( RGE_Engine tmxlite )

target_link_libraries( RGE_Engine lua )

#target_include_directories( RGE_Engine INTERFACE $(CMAKE_CURRENT_SOURCE_DIR))