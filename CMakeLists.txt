cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(RetroGameEngine_Old VERSION 1)

SET( LIBS_DIR       "${PROJECT_SOURCE_DIR}/Engine/libs")
SET( LUA_DIR        "${LIBS_DIR}/lua" )
SET( SOL2_DIR       "${LIBS_DIR}/sol" )

# Build lua library
#add_library(
#        lua STATIC
#        ${LUA_DIR}/lapi.c
#        ${LUA_DIR}/lauxlib.c
#        ${LUA_DIR}/lbaselib.c
#        ${LUA_DIR}/lcode.c
#        ${LUA_DIR}/lcorolib.c
#        ${LUA_DIR}/lctype.c
#        ${LUA_DIR}/ldblib.c
#        ${LUA_DIR}/ldebug.c
#        ${LUA_DIR}/ldo.c
#        ${LUA_DIR}/ldump.c
#        ${LUA_DIR}/lfunc.c
#        ${LUA_DIR}/lgc.c
#        ${LUA_DIR}/linit.c
#        ${LUA_DIR}/liolib.c
#        ${LUA_DIR}/llex.c
#        ${LUA_DIR}/lmathlib.c
#        ${LUA_DIR}/lmem.c
#        ${LUA_DIR}/loadlib.c
#        ${LUA_DIR}/lobject.c
#        ${LUA_DIR}/lopcodes.c
#        ${LUA_DIR}/loslib.c
#        ${LUA_DIR}/lparser.c
#        ${LUA_DIR}/lstate.c
#        ${LUA_DIR}/lstring.c
#        ${LUA_DIR}/lstrlib.c
#        ${LUA_DIR}/ltable.c
#        ${LUA_DIR}/ltablib.c
#        ${LUA_DIR}/ltm.c
#        ${LUA_DIR}/lua.c
#        ${LUA_DIR}/lundump.c
#        ${LUA_DIR}/lutf8lib.c
#        ${LUA_DIR}/lvm.c
#        ${LUA_DIR}/lzio.c
#)

# Engine
set(ENGINE_SOURCE_FILES
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
        Engine/src/Components/include/SpritesheetComponent.h

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

        Engine/src/FSM/include/BaseState.h
        Engine/src/FSM/include/FSM.h
        Engine/src/FSM/include/States.h
        Engine/src/FSM/FSM.cpp
        Engine/src/FSM/StateTransitions.cpp

        Engine/src/LevelLoader/include/LevelLoader.h
        Engine/src/LevelLoader/LevelLoader.cpp

        Engine/src/Systems/include/AnimationSystem.h
        Engine/src/Systems/include/CameraFollowSystem.h
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
        Engine/src/Systems/include/RenderSystem.h
        Engine/src/Systems/include/RenderTextSystem.h
        Engine/src/Systems/include/EditorSystem.h
        Engine/src/FileHandler/include/FileHandler.h
        Engine/src/FileHandler/FileHandler.cpp
        Engine/src/Components/include/FSMComponent.h
        Engine/src/Components/include/SpritesheetComponent.h
)


SET(EDITOR_SOURCE_FILES

#        Editor/src/Editor.cpp
        Editor/libs/imgui_docking/imgui.cpp
        Editor/libs/imgui_docking/imgui_demo.cpp
        Editor/libs/imgui_docking/imgui_draw.cpp
        Editor/libs/imgui_docking/imgui_tables.cpp
        Editor/libs/imgui_docking/imgui_widgets.cpp
        Editor/libs/imgui_docking/backends/imgui_impl_sdl2.cpp
        Editor/libs/imgui_docking/backends/imgui_impl_sdlrenderer2.cpp
        Editor/libs/imgui_docking/misc/cpp/imgui_stdlib.h
        Editor/libs/imgui_docking/misc/cpp/imgui_stdlib.cpp

        Editor/src/Displays/TestDisplayA.cpp
        Editor/src/Displays/EntityDisplay.cpp
        Editor/src/Displays/SceneDisplay.cpp
        Editor/src/Displays/MainMenuBar.cpp
        Editor/src/Displays/MainMenuBar.h
        Editor/src/Displays/LogDisplay.cpp
        Editor/src/Displays/LogDisplay.h
        Editor/src/Displays/EntityDisplay.h
        Editor/src/Displays/FileDisplay.cpp
        Editor/src/Displays/FileDisplay.h
        Editor/src/Displays/DebugDisplay.cpp
        Editor/src/Displays/DebugDisplay.h
        Editor/src/Displays/ProjectMenuDisplay.h
        Editor/src/Displays/ProjectMenuDisplay.cpp
        Editor/src/Displays/MouseDisplay.cpp
        Editor/src/Logger/include/Logger.h
        Editor/src/Logger/src/Logger.cpp
        Editor/src/Logger/include/TerminalLogger.h
        Editor/src/Logger/src/TerminalLogger.cpp

#        Editor/src/FileSystem/src/FileDialogs.cpp
#        Editor/src/FileSystem/include/FileDialogs.h

        Editor/src/FileSystem/include/FileHandler.h
        Editor/src/FileSystem/src/FileHandler.cpp
        Editor/src/FileSystem/src/NativeFileDialogExt.cpp

        Editor/libs/ImGuiFileDialog/ImGuiFileDialog.h
        Editor/libs/ImGuiFileDialog/ImGuiFileDialog.cpp
)

SET(GAME_SOURCE_FILES
        Engine_Test_Game_Platform/src/GameHook.cpp
)

link_directories( /usr/local/lib )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable( ${PROJECT_NAME} ${ENGINE_SOURCE_FILES} ${EDITOR_SOURCE_FILES} ${GAME_SOURCE_FILES})

include_directories(
        Engine/include/
        Engine/libs/lua/
        Engine/libs/sol/

        Engine/src/AssetStore/
        Engine/src/Components/
        Engine/src/ECS/
        Engine/src/EventBus/
        Engine/src/Events/
        Engine/src/FileHandler/
        Engine/src/FSM/
        Engine/src/LevelLoader/
        Engine/src/Systems/

        Editor/libs/imgui_docking/
        Editor/libs/imgui_docking/backends/
        Editor/libs/nativefiledialog-extended/
        Editor/src/Displays/
        Editor/src/Logger/
)

add_subdirectory(Editor/libs/nativefiledialog-extended)
target_link_libraries(${PROJECT_NAME} nfd)

include_directories( /usr/local/include ${LUA_INCLUDE_DIR} )

target_include_directories( ${PROJECT_NAME} PUBLIC ${LIBS_DIR} PUBLIC ${LUA_DIR} )

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

target_link_libraries( RetroGameEngine_Old tmxlite )

target_link_libraries( RetroGameEngine_Old lua )
