//
// Created by Darren Tynan on 17/11/2024.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../include/Game.h"

int Game::windowWidth;
int Game::windowHeight;
int Game::mapWidth;
int Game::mapHeight;

//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

Game::Game()
{
    isRunning = false;
    isDebug = false;
//    Logger::Log("Game constructor called");
}

Game::~Game()
{
//    Logger::Log("Game deconstruct called");
}

int Game::Initialize()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480,
                                          0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

//    SDL_UpdateWindowSurface(window);

//    SDL_Delay(10000);
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }

    return 0;





//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
//    {
//        std::cout << "SDL could not be initialised\n" << SDL_GetError();
//        return;
//    }
//
//    if (TTF_Init() != 0)
//    {
////        Logger::Error("Error initializing SDL TTF");
//        return;
//    }
//
//    SDL_DisplayMode displayMode;
//    SDL_GetCurrentDisplayMode(0, &displayMode);
//    windowWidth = 640;
//    windowHeight = 480;
////    windowWidth = displayMode.w;
////    windowHeight = displayMode.h;
//
//
//    window = SDL_CreateWindow(
//            "Game",
//            SDL_WINDOWPOS_CENTERED,
//            SDL_WINDOWPOS_CENTERED,
//            windowWidth,
//            windowHeight,
//            SDL_WINDOW_SHOWN
//    );
//
//    if (!window)
//    {
//        std::cerr << "Window init failed" << std::endl;
//        return;
//    }
//
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (!renderer)
//    {
//        std::cerr << "Window renderer init failed" << std::endl;
//        return;
//    }
//
//    // Initialize the camera view with the entire screen area
//    camera.x = 0;
//    camera.y = 0;
//    camera.w = windowWidth;
//    camera.h = windowHeight;
//
//    std::cout << "SDL is ready to go!\n";
////    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
//    isRunning = true;
//
//    // Setup Dear ImGui context
////    IMGUI_CHECKVERSION();
////    ImGui::CreateContext();
////    ImGuiIO& io = ImGui::GetIO(); (void)io;
//
//    // Setup Dear ImGui style
////    ImGui::StyleColorsDark();
//
//    // Setup Platform/Renderer backends
////    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
////    ImGui_ImplSDLRenderer_Init(renderer);
}


void Game::Run()
{
    Render();
//    SetUpGameObjects();

//    while (isRunning)
//    {
//        ProcessInput();
//        UpdateSystems();
//        Render();
//    }
}


void Game::Destroy()
{
//    ImGui_ImplSDLRenderer_Shutdown();
//    ImGui_ImplSDL2_Shutdown();
//    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
//    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render
//    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
//    registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore, camera);

//    if (isDebug) {
//        registry->GetSystem<RenderColliderSystem>().Update(renderer, camera);
//        auto player = registry->GetEntityByTag("player");
//        registry->GetSystem<RenderRaycastSystem>().Update(renderer, player);
//    }

//    if (isImGui) {
//        registry->GetSystem<RenderImGuiSystem>().Update(registry, camera);
//    }

    // Display HUD
//    SDL_Texture* hud = assetStore->GetTexture("hud");
//    SDL_Rect source;
//    source.x = 0;
//    source.y = 0;
//    source.w = 640;
//    source.h = 64;
//
//    SDL_Rect destination;
//    destination.x = 0;
//    destination.y = 480-64;
//    destination.w = 640;
//    destination.h = 64;
//
//    SDL_RenderCopy(renderer, hud, &source, &destination);
//
//    SDL_RenderPresent(renderer);
}

