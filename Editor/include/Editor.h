//
// Created by Darren Tynan on 06/01/2025.
//

#ifndef RETROGAMEENGINE_EDITOR_H
#define RETROGAMEENGINE_EDITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class Editor
{
public:
    static void SetupSDL();
    static void Run();
    static void Destroy();
    static bool ProcessDebugInputEvents();
    static void SetupImGui();

};

#endif //RETROGAMEENGINE_EDITOR_H
