//
// Created by Darren Tynan on 06/01/2025.
//

#ifndef RETROGAMEENGINE_EDITOR_H
#define RETROGAMEENGINE_EDITOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Editor
{
public:
    static void Setup();
    static void Run();
    static void Destroy();
    static bool ProcessDebugInputEvents();

};

#endif //RETROGAMEENGINE_EDITOR_H
