//
// Created by Darren Tynan on 14/01/2025.
//

#include "SceneDisplay.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

EDITOR::SceneDisplay::SceneDisplay() {}

void EDITOR::SceneDisplay::Draw()
{
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    ImGui::SetNextWindowSize(ImVec2(800, 600));
    ImGui::SetNextWindowPos(ImVec2((displayMode.w - 800) / 2, 0)); // Set the position of the new window
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

    if (ImGui::Begin("Scene"))
    {
        ImGui::Button("Play");
        ImGui::SameLine();
        ImGui::Button("Stop");

    }
    ImGui::End();

}