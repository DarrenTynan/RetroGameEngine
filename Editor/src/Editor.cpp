//
// Created by Darren Tynan on 06/01/2025.
//

#include <iostream>
#include "../include/Editor.h"
#include "../../Engine/src/Logger/Logger.h"

SDL_Window* editorWindow;
SDL_Renderer* editorRenderer;

void Editor::Setup()
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL could not be initialised\n" << SDL_GetError();
        Logger::Error2Arg("SDL could not be initialised ", SDL_GetError());
        exit(1);
    }

    // Setup true type fonts
    if (TTF_Init() != 0)
    {
        Logger::Error("Error initializing SDL TTF");
        exit(1);
    }

    // From 2.0.18: Enable native IME.
    #ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

    Logger::Log("SDL is ready to go!");

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    // Create window with SDL_Renderer graphics context
    auto windowFlags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    editorWindow = SDL_CreateWindow(
            "Retro Game Engine v1",
            0,
            0,
            displayMode.w,
            displayMode.h,
            windowFlags
    );

    if (!editorWindow)
    {
        Logger::Error("Window init failed");
        SDL_Quit();
        exit(1);
    }

    editorRenderer = SDL_CreateRenderer(editorWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!editorRenderer)
    {
        Logger::Error("Window renderer init failed");
        SDL_DestroyRenderer(editorRenderer);
        SDL_Quit();
        exit(1);
    }

}

/**
 * Poll window events:
 *
 * window quit
 * keyboard
 */
bool Editor::ProcessDebugInputEvents()
{
    bool isQuit = true;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        // ImGui
//        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
//        ImGuiIO io = ImGui::GetIO();
//        int mouseX;
//        int mouseY;
//        const unsigned int buttons = SDL_GetMouseState(&mouseX, &mouseY);
//        io.MousePos = ImVec2((float)mouseX, (float)mouseY);
//        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
//        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

        // Core sdl events.
        switch (sdlEvent.type)
        {
            // Window close
            case SDL_QUIT:
                isQuit = false;
                break;

            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { isQuit = false; }
                break;

                // Check for window event
            case SDL_WINDOWEVENT:

                switch (sdlEvent.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        isQuit = false;
                        break;
                }
                break;
        }
    };
    return isQuit;
};

void Editor::Run()
{
    bool isGameRunning = true;
    while (isGameRunning)
    {
        isGameRunning = Editor::ProcessDebugInputEvents();
    }
}

void Editor::Destroy()
{
//    ImGui_ImplSDLRenderer2_Shutdown();
//    ImGui_ImplSDL2_Shutdown();
//    ImGui::DestroyContext();

    SDL_DestroyWindow(editorWindow);
    SDL_DestroyRenderer(editorRenderer);

    SDL_Quit();

}
