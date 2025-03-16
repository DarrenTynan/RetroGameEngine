cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(RGE)

SET( SRC_DIR        "${PROJECT_SOURCE_DIR}/src" )
SET( LIBS_DIR       "${PROJECT_SOURCE_DIR}/libs" )
SET( LUA_DIR        "${LIBS_DIR}/lua" )
SET( SOL2_DIR       "${LIBS_DIR}/sol" )

# Build lua library
add_library(
        lua STATIC
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
        ../Game_Test/main.cpp
)

add_library(RGE STATIC
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
        ${SRC_DIR}/Components/include/TextLabelComponent.h
        ${SRC_DIR}/Components/include/TransformComponent.h

        ${SRC_DIR}/ECS/include/ECS.h
        ${SRC_DIR}/ECS/include/Component.h
        ${SRC_DIR}/ECS/include/Entity.h
        ${SRC_DIR}/ECS/include/Pool.h
        ${SRC_DIR}/ECS/include/Registry.h
        ${SRC_DIR}/ECS/ECS.cpp

        ${SRC_DIR}/EventBus/include/Event.h
        ${SRC_DIR}/EventBus/include/EventBus.h

        ${SRC_DIR}/Events/include/CollisionEvent.h
        ${SRC_DIR}/Events/include/KeyPressedEvent.h
        ${SRC_DIR}/Events/include/KeyReleasedEvent.h

        ${SRC_DIR}/FSM/include/BaseState.h
        ${SRC_DIR}/FSM/include/FSM.h
        ${SRC_DIR}/FSM/include/States.h
        ${SRC_DIR}/FSM/FSM.cpp
        ${SRC_DIR}/FSM/StateTransitions.cpp

        ${SRC_DIR}/LevelLoader/include/LevelLoader.h
        ${SRC_DIR}/LevelLoader/LevelLoader.cpp

        ${SRC_DIR}/Systems/include/AnimationSystem.h
        ${SRC_DIR}/Systems/include/CameraMovementSystem.h
        ${SRC_DIR}/Systems/include/CollisionSystem.h
        ${SRC_DIR}/Systems/include/DamageSystem.h
        ${SRC_DIR}/Systems/include/MovementSystem.h
        ${SRC_DIR}/Systems/include/PlayerControllerSystem.h
        ${SRC_DIR}/Systems/include/ProjectileEmitSystem.h
        ${SRC_DIR}/Systems/include/ProjectileLifecycleSystem.h
        ${SRC_DIR}/Systems/include/RenderColliderSystem.h
        ${SRC_DIR}/Systems/include/RenderHealthBarSystem.h
        ${SRC_DIR}/Systems/include/RenderRayCastSystem.h
        ${SRC_DIR}/Systems/include/RenderSystem.h
        ${SRC_DIR}/Systems/include/RenderTextSystem.h
        ${SRC_DIR}/Systems/include/ScriptSystem.h

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
)

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( SDL2_TTF REQUIRED )
find_package( GLM REQUIRED )
find_package( Lua REQUIRED )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
target_link_libraries( RGE tmxlite )
target_link_libraries( RGE lua )

#add_subdirectory(${SRC_DIR}/AssetStore)