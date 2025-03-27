cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(RetroGameEngine)

SET( LIBS_DIR       "${PROJECT_SOURCE_DIR}/Engine/libs")
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
)

# Engine
set(SOURCE_FILES
        main.cpp

        Engine/include/RGE.h
        Engine/src/RGE.cpp
        Engine/libs/sol/sol.hpp

        Engine/src/AssetStore/include/AssetStore.h
        Engine/src/AssetStore/src/AssetStore.cpp

        Engine/src/Components/include/AnimationComponent.h
        Engine/src/Components/include/BoxColliderComponent.h
        Engine/src/Components/include/CameraFollowComponent.h
        Engine/src/Components/include/HealthComponent.h
        Engine/src/Components/include/ProjectileComponent.h
        Engine/src/Components/include/ProjectileEmitterComponent.h
        Engine/src/Components/include/RaycastComponent.h
        Engine/src/Components/include/RigidBodyComponent.h
        Engine/src/Components/include/ScriptComponent.h
        Engine/src/Components/include/SpriteComponent.h
        Engine/src/Components/include/TextLabelComponent.h
        Engine/src/Components/include/TransformComponent.h

        Engine/src/ECS/include/Component.h
        Engine/src/ECS/include/ECS.h
        Engine/src/ECS/include/Entity.h
        Engine/src/ECS/include/Pool.h
        Engine/src/ECS/include/Registry.h
        Engine/src/ECS/include/System.h
        Engine/src/ECS/ECS.cpp

        Engine/src/EventBus/include/Event.h
        Engine/src/EventBus/include/EventBus.h

        Engine/src/Events/include/CollisionEvent.h
#        Engine/src/Events/include/KeyPressedEvent.h
#        Engine/src/Events/include/KeyReleasedEvent.h

        Engine/src/FSM/include/BaseState.h
        Engine/src/FSM/include/FSM.h
        Engine/src/FSM/include/States.h
        Engine/src/FSM/FSM.cpp
        Engine/src/FSM/StateTransitions.cpp

        Engine/src/LevelLoader/include/LevelLoader.h
        Engine/src/LevelLoader/LevelLoader.cpp

        Engine/src/Systems/include/AnimationSystem.h
        Engine/src/Systems/include/CameraMovementSystem.h
        Engine/src/Systems/include/PlayerCollisionSystem.h
        Engine/src/Systems/include/EntityCollisionSystem.h
        Engine/src/Systems/include/DamageSystem.h
        Engine/src/Systems/include/EntityMovementSystem.h
        Engine/src/Systems/include/PlayerControllerSystem.h
        Engine/src/Systems/include/PlayerControllerSystem.h
        Engine/src/Systems/include/ProjectileEmitSystem.h
        Engine/src/Systems/include/ProjectileLifecycleSystem.h
        Engine/src/Systems/include/RenderColliderSystem.h
        Engine/src/Systems/include/RenderHealthBarSystem.h
        Engine/src/Systems/include/RenderRaycastSystem.h
        Engine/src/Systems/include/RenderRaycastSystem.h
        Engine/src/Systems/include/RenderSystem.h
        Engine/src/Systems/include/RenderTextSystem.h

        Engine_Test_Game_Platform/src/Game.cpp

        Engine/src/FileHandler/include/FileHandler.h
        Engine/src/FileHandler/FileHandler.cpp

)

link_directories( /usr/local/lib )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

include_directories(
        Engine_Test_Game_Platform/assets/
        Engine_Test_Game_Platform/include/
        Engine_Test_Game_Platform/scripts/
        Engine_Test_Game_Platform/src/

        Engine/include/
        Engine/libs/lua/
        Engine/libs/sol/
)

include_directories( /usr/local/include ${LUA_INCLUDE_DIR} )

target_include_directories( ${PROJECT_NAME} PUBLIC ${LIBS_DIR} PUBLIC ${LUA_DIR} )

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( SDL2_TTF REQUIRED )
find_package( GLM REQUIRED )
find_package( Lua REQUIRED )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)

target_link_libraries( RetroGameEngine tmxlite )

target_link_libraries( RetroGameEngine lua )
