cmake_minimum_required(VERSION 3.24)
project(RetroGameEngine)

set(CMAKE_CXX_STANDARD 17)

# Make my library fie.
#add_library(RGE STATIC RGE/src/RGE.cpp)

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES main.cpp
#        Game/include/Game.h
        Game/src/Game.cpp
#        RGE/include/RGE.h
        RGE/src/RGE.cpp

        RGE/src/Logger/Logger.cpp

        RGE/libs/imgui_docking/imgui.cpp
        RGE/libs/imgui_docking/imgui_demo.cpp
        RGE/libs/imgui_docking/imgui_draw.cpp
        RGE/libs/imgui_docking/imgui_tables.cpp
        RGE/libs/imgui_docking/imgui_widgets.cpp
        RGE/libs/imgui_docking/backends/imgui_impl_sdl2.cpp
        RGE/libs/imgui_docking/backends/imgui_impl_sdlrenderer2.cpp

        RGE/src/AssetStore/AssetStore.cpp
        RGE/src/ECS/ECS.cpp
        RGE/src/Logger/Logger.cpp
        RGE/src/ECS/include/Pool.h
        RGE/src/ECS/include/Component.h
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(RGE/libs/imgui_docking/ RGE/libs/imgui_docking/backends/ Game/assets)

# Line compiles but missing error.
#target_link_libraries(${PROJECT_NAME} /RGE/libs/libRGE.a)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(GLM REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)

target_link_libraries(RetroGameEngine tmxlite)
