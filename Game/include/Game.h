//
// Created by Darren Tynan on 17/11/2024.
//

#ifndef RETROGAMEENGINE_GAME_H
#define RETROGAMEENGINE_GAME_H

#include <iostream>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include "../../RGE/src/Logger/Logger.h"

// Global vars
const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Surface* windowSurface = nullptr;
        SDL_Rect camera;

        bool isRunning = false;
        bool isDebug = false;
        bool isImGui = false;
        bool isFullScreen = false;
        int millisecsPreviouseFrame = 0;
        int windowWidth = 640;
        int windowHeight = 480;
        int mapWidth;
        int mapHeight;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    public:
        Game();
        virtual ~Game();

        int Initialize();

        void Run();
//        int GetTMX();
        void SetUpGameObjects();
//        void ProcessInput();
        void UpdateSystems();
        void Render();
        void RenderImGui();
        void Destroy();
        void RenderTree();
};

#endif //RETROGAMEENGINE_GAME_H
