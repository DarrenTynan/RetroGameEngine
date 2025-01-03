cmake_minimum_required(VERSION 3.24)
project(RetroGameEngine)

set(CMAKE_CXX_STANDARD 17)

# Make my library fie.
#add_library(RGE STATIC RGE/src/RGE.cpp)

SET( LIBS_DIR "${PROJECT_SOURCE_DIR}/RGE/libs")
SET( LUA_DIR "${LIBS_DIR}/lua" )
SET( SOL2_DIR "${LIBS_DIR}/sol" )

# lua lib
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


# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES
        main.cpp

        RGE/include/Globals.h
        RGE/include/Config.h
        RGE/include/RGE.h
        RGE/src/RGE.cpp

        RGE/libs/imgui_docking/imgui.cpp
        RGE/libs/imgui_docking/imgui_demo.cpp
        RGE/libs/imgui_docking/imgui_draw.cpp
        RGE/libs/imgui_docking/imgui_tables.cpp
        RGE/libs/imgui_docking/imgui_widgets.cpp
        RGE/libs/imgui_docking/backends/imgui_impl_sdl2.cpp
        RGE/libs/imgui_docking/backends/imgui_impl_sdlrenderer2.cpp

        RGE/libs/sol/sol.hpp

        RGE/src/AssetStore/AssetStore.cpp
        RGE/src/Logger/Logger.cpp
        RGE/src/ECS/ECS.cpp
        RGE/src/ECS/include/Pool.h
        RGE/src/ECS/include/Component.h
        RGE/src/ECS/include/Entity.h
        RGE/src/ECS/include/System.h
        RGE/src/ECS/include/Registry.h
        RGE/src/LevelLoader/LevelLoader.h
        RGE/src/LevelLoader/LevelLoader.cpp

        RGE/src/FSM/include/FSM.h
        RGE/src/FSM/FSM.cpp
        RGE/src/FSM/include/BaseState.h
        RGE/src/FSM/include/States.h
        RGE/src/FSM/StateTransitions.cpp

        Game/src/Game.cpp
        Game/scripts/Level1.lua
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(
        Game/assets/
        RGE/include/
        RGE/libs/imgui_docking/
        RGE/libs/imgui_docking/backends/
        RGE/libs/lua/
        RGE/libs/sol/
)

# Line compiles but missing error.
#target_link_libraries(${PROJECT_NAME} /RGE/libs/libRGE.a)

target_include_directories( ${PROJECT_NAME} PUBLIC ${LIBS_DIR} PUBLIC ${LUA_DIR} )

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(GLM REQUIRED)

find_package(Lua REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)

target_link_libraries( RetroGameEngine tmxlite )

target_link_libraries( RetroGameEngine lua )
