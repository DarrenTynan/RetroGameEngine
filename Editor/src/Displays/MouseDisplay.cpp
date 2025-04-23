//
// Created by Darren Tynan on 14/01/2025.
//

#include "MouseDisplay.h"
#include "include/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "../src/Systems/include/EditorSystem.h"
#include "../../src/Components/include/TransformComponent.h"
#include "../../src/Components/include/RigidBodyComponent.h"

using namespace EDITOR_LOGGER;
using namespace RGE_System;
using namespace RGE_Component;

namespace EDITOR
{

    EDITOR::MouseDisplay::MouseDisplay()
    {
        name = "MouseDisplay";
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();

    };

    int mouseX, mouseY;
    SDL_Event sdlEvent;

    void EDITOR::MouseDisplay::Render(std::shared_ptr<Registry>& registry)
    {
        if (ImGui::Begin("Mouse Events"))
        {
            auto editorSystem = registry->GetSystem<EditorSystem>();
            bool hb = static_cast<bool>(editorSystem.hitBox);
            bool bc = static_cast<bool>(editorSystem.showBoxCollider);
            bool grid = static_cast<bool>(editorSystem.showGrid);

            SDL_GetMouseState(&mouseX, &mouseY);
            ImGui::Text("mouse x: %i, y: %i", mouseX, mouseY);
            ImGui::SameLine(180.0f);
            ImGui::SetNextItemWidth(130);
            ImGui::Checkbox("Hit Box", &hb);
            ImGui::Separator();

            ImGui::Checkbox("Box Collider", &bc);
            ImGui::SameLine(180.0f);
            ImGui::SetNextItemWidth(130);
            ImGui::Checkbox("Show Grid", &grid);
            ImGui::Separator();

            std::string entityTag = editorSystem.entityTag;

            ImGui::Text("Entity Tag: %s", entityTag.c_str());
            ImGui::Text("Entity ID: %i", registry->GetSystem<EditorSystem>().entityID);

        }
        ImGui::End();

    }

} // end namespace