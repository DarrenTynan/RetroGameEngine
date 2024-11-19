//
// Created by Darren Tynan on 17/11/2024.
//

#ifndef RETROGAMEENGINE_GAME_H
#define RETROGAMEENGINE_GAME_H

#include <SDL2/SDL.h>

class Game
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect camera;
        bool isRunning = false;
        bool isDebug = false;
        bool isImGui = false;
        int millisecsPreviouseFrame = 0;

    public:
        Game();
        virtual ~Game();

        int Initialize();
        void Run();
//        int GetTMX();
//        void SetUpGameObjects();
//        void ProcessInput();
//        void UpdateSystems();
        void Render();
        void Destroy();

        static int windowWidth;
        static int windowHeight;
        static int mapWidth;
        static int mapHeight;
};

#endif //RETROGAMEENGINE_GAME_H
