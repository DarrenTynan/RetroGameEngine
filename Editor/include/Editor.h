//
// Created by Darren Tynan on 06/01/2025.
//

#ifndef RETROGAMEENGINE_EDITOR_H
#define RETROGAMEENGINE_EDITOR_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include "../src/Logger/include/TerminalLogger.h"
//#include "../src/Logger/include/Logger.h" // NOT working yet

#include "../src/Displays/TestDisplayA.h"
#include "../src/Displays/EntityDisplay.h"
#include "../src/Displays/SceneDisplay.h"
#include "../src/Displays/MainMenuBar.h"
#include "../src/Displays/LogDisplay.h"
#include "../src/Displays/DebugDisplay.h"
#include "../src/Displays/FileDisplay.h"
#include "../src/Displays/MouseDisplay.h"
//#include "../src/Displays/ProjectMenuDisplay.h"

//#include "../FileSystem/include/FileHandler.h"


namespace EDITOR
{
    class Editor
    {
    public:
        void Setup();
        void Run();
        void Destroy();
//        std::string project_name;
        std::string file_path;
        int window_width;
        int window_height;
        std::string window_title;

        static void OpenEditorWindow();

        static void SetupImGui();
    private:
        void OpenProjectWindow();

        static bool mousePress(SDL_MouseButtonEvent &b);
    };

}

#endif //RETROGAMEENGINE_EDITOR_H
