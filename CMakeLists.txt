cmake_minimum_required(VERSION 3.24)
project(RetroGameEngine)

set(CMAKE_CXX_STANDARD 23)

# Make my library fie.
#add_library(RGE STATIC RGE/src/RGE.cpp)

# Add main.cpp file of the project root directory as a source file

set(SOURCE_FILES main.cpp
                    Game/src/Game.cpp
                    RGE/src/Logger/Logger.cpp

#                    RGE/libs/imgui/imconfig.h
#                    RGE/libs/imgui/imgui.h
#                    RGE/libs/imgui/imgui_internal.h
#                    RGE/libs/imgui/imstb_rectpack.h
#                    RGE/libs/imgui/imstb_textedit.h
#                    RGE/libs/imgui/imstb_truetype.h

#                    RGE/libs/imgui/backends/imgui_impl_sdl2.h
#                    RGE/libs/imgui/backends/imgui_impl_sdlrenderer2.h
                    RGE/libs/imgui/backends/imgui_impl_sdl2.cpp
                    RGE/libs/imgui/backends/imgui_impl_sdlrenderer2.cpp

                    RGE/libs/imgui/imgui.cpp
                    RGE/libs/imgui/imgui_demo.cpp
                    RGE/libs/imgui/imgui_draw.cpp
                    RGE/libs/imgui/imgui_tables.cpp
                    RGE/libs/imgui/imgui_widgets.cpp
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(RGE/libs/imgui/ RGE/libs/imgui/backends/)

# Line compiles but missing error.
#target_link_libraries(${PROJECT_NAME} /RGE/libs/libRGE.a)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)

include_directories(libs)
