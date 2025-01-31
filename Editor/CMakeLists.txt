cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(Editor)

#       Editor
set(SOURCE_FILES
        main.cpp
        src/Editor.cpp

        libs/imgui_docking/imgui.cpp
        libs/imgui_docking/imgui_demo.cpp
        libs/imgui_docking/imgui_draw.cpp
        libs/imgui_docking/imgui_tables.cpp
        libs/imgui_docking/imgui_widgets.cpp
        libs/imgui_docking/backends/imgui_impl_sdl2.cpp
        libs/imgui_docking/backends/imgui_impl_sdlrenderer2.cpp
        libs/imgui_docking/misc/cpp/imgui_stdlib.h
        libs/imgui_docking/misc/cpp/imgui_stdlib.cpp

        src/Displays/TestDisplayA.cpp
        src/Displays/TestDisplayB.cpp
        src/Displays/SceneDisplay.cpp
        src/Displays/MainMenuBar.cpp
        src/Displays/MainMenuBar.h
        src/Displays/LogDisplay.cpp
        src/Displays/LogDisplay.h
        src/Displays/TestDisplayB.h
        src/Displays/FileDisplay.cpp
        src/Displays/FileDisplay.h
        src/Displays/DebugDisplay.cpp
        src/Displays/DebugDisplay.h
        src/Displays/ProjectMenuDisplay.h
        src/Displays/ProjectMenuDisplay.cpp

        src/Logger/include/Logger.h
        src/Logger/src/Logger.cpp
        src/Logger/include/TerminalLogger.h
        src/Logger/src/TerminalLogger.cpp

        src/FileSystem/src/FileDialogs.cpp
        src/FileSystem/include/FileDialogs.h
        src/FileSystem/include/FileHandler.h
        src/FileSystem/src/FileHandler.cpp

)

link_directories( /usr/local/lib )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

include_directories(
        /usr/local/include
        include/
        libs/imgui_docking/
        libs/imgui_docking/backends/
        libs/nativefiledialog-extended/
        src/Displays/
        src/Logger/
)

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( SDL2_TTF REQUIRED )

target_link_libraries(${PROJECT_NAME} nfd)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
