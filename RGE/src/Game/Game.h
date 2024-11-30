//
// Created by Darren Tynan on 26/12/2022.
//

#ifndef RETRO_ENGINE_GAME_H
#define RETRO_ENGINE_GAME_H

#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../EventBus/EventBus.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect camera;
        bool isRunning = false;
        bool isDebug = false;
        bool isImGui = false;
        int millisecsPreviouseFrame = 0;

        std::unique_ptr<Registry> registry;
        std::unique_ptr<AssetStore> assetStore;
        std::unique_ptr<EventBus> eventBus;

    public:
        Game();
        virtual ~Game();

        void Initialize();
        void Run();
        int SetupTMX();
        void SetUpGameObjects();
        void ProcessInput();
        void UpdateSystems();
        void Render();
        void Destroy();

        static int windowWidth;
        static int windowHeight;
        static int mapWidth;
        static int mapHeight;
};

#endif //RETRO_ENGINE_GAME_H
