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

//#include "../libs/tinyfiledialogs/tinyfiledialogs.h"
#include "../libs/nativefiledialog-extended/src/include/nfd.h"

#include "../src/Logger/Logger.h"

#include "../src/displays/TestDisplayA.h"
#include "../src/displays/TestDisplayB.h"
#include "../src/displays/SceneDisplay.h"
#include "../src/displays/MainMenuBar.h"

namespace EDITOR
{
    class Editor
    {
    public:
        void SetupSDL();
        void Run();
        void Destroy();
        bool ProcessDebugInputEvents();
        void SetupImGui();
//        void Test();
//        void RenderImGui();
        void CreateDisplays();
        void FileLoader();

    };

}

#endif //RETROGAMEENGINE_EDITOR_H
