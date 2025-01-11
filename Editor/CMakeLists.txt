cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(Editor)

#       Editor
set(SOURCE_FILES
        main.cpp
        src/Editor.cpp

        src/Logger/Logger.cpp
        libs/imgui_docking/imgui.cpp
        libs/imgui_docking/imgui_demo.cpp
        libs/imgui_docking/imgui_draw.cpp
        libs/imgui_docking/imgui_tables.cpp
        libs/imgui_docking/imgui_widgets.cpp
        libs/imgui_docking/backends/imgui_impl_sdl2.cpp
        libs/imgui_docking/backends/imgui_impl_sdlrenderer2.cpp
)

link_directories( /usr/local/lib )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

include_directories(
        /usr/local/include
        include/
        libs/imgui_docking/
        libs/imgui_docking/backends
)

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( SDL2_TTF REQUIRED )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
