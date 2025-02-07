cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(RetroGameEngine)

# Make my library fie.
#add_library(RGE STATIC
#        Engine/src/RGE.cpp
#)

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


# Editor
#set(SOURCE_FILES_EDITOR
#        Editor/main.cpp
#        Editor/src/Editor.cpp
#
#        Editor/libs/imgui_docking/imgui.cpp
#        Editor/libs/imgui_docking/imgui_demo.cpp
#        Editor/libs/imgui_docking/imgui_draw.cpp
#        Editor/libs/imgui_docking/imgui_tables.cpp
#        Editor/libs/imgui_docking/imgui_widgets.cpp
#        Editor/libs/imgui_docking/backends/imgui_impl_sdl2.cpp
#        Editor/libs/imgui_docking/backends/imgui_impl_sdlrenderer2.cpp
#        Editor/src/Logger/Logger.cpp
#)

# Engine
set(SOURCE_FILES_ENGINE
        main.cpp

        Engine/include/Config.h
        Engine/include/RGE.h
        Engine/src/RGE.cpp

        Engine/libs/sol/sol.hpp

        Engine/src/AssetStore/AssetStore.cpp
        Engine/src/ECS/ECS.cpp
        Engine/src/ECS/include/Pool.h
        Engine/src/ECS/include/Component.h
        Engine/src/ECS/include/Entity.h
        Engine/src/ECS/include/System.h
        Engine/src/ECS/include/Registry.h
        Engine/src/LevelLoader/LevelLoader.h
        Engine/src/LevelLoader/LevelLoader.cpp

        Engine/src/FSM/include/FSM.h
        Engine/src/FSM/FSM.cpp
        Engine/src/FSM/include/BaseState.h
        Engine/src/FSM/include/States.h
        Engine/src/FSM/StateTransitions.cpp

        Game/src/Game.cpp

)

add_subdirectory(Editor)

link_directories( /usr/local/lib )

# Add executable target with source files listed in SOURCE_FILES variable
#add_executable( ${PROJECT_NAME} ${SOURCE_FILES_EDITOR} ${SOURCE_FILES_ENGINE} )
add_executable( ${PROJECT_NAME} ${SOURCE_FILES_ENGINE} )

#include_directories(
#        Editor/include/
#        Editor/libs/imgui_docking/
#        Editor/libs/imgui_docking/backends
#)

include_directories(
        Game/assets/
        Game/include/
        Game/scripts/
        Game/src/

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
