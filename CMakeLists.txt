cmake_minimum_required(VERSION 3.24)
project(RetroGameEngine)

set(CMAKE_CXX_STANDARD 20)

# Make my library fie.
#add_library(RGE STATIC RGE/src/RGE.cpp)

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES main.cpp
        Game/src/Game.cpp
        RGE/src/Logger/Logger.cpp
        
        RGE/libs/imgui_basic/imgui.cpp
        RGE/libs/imgui_basic/imgui_demo.cpp
        RGE/libs/imgui_basic/imgui_draw.cpp
        RGE/libs/imgui_basic/imgui_tables.cpp
        RGE/libs/imgui_basic/imgui_widgets.cpp
        RGE/libs/imgui_basic/backends/imgui_impl_sdl2.cpp
        RGE/libs/imgui_basic/backends/imgui_impl_sdlrenderer2.cpp

        RGE/src/AssetStore/AssetStore.cpp
        RGE/src/ECS/ECS.cpp
        RGE/src/Logger/Logger.cpp
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(RGE/libs/imgui_basic/ RGE/libs/imgui_basic/backends/ Game/assets)

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
