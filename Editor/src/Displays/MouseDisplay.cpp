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

//    bool hitBox = false;
    int mouseX, mouseY;
    SDL_Event sdlEvent;
//    std::string entityTag = "null";

    void EDITOR::MouseDisplay::Render(std::shared_ptr<Registry>& registry)
    {
        if (ImGui::Begin("Mouse Events"))
        {
            auto editorSystem = registry->GetSystem<EditorSystem>();
            bool hb = static_cast<bool>(editorSystem.hitBox);
            SDL_GetMouseState(&mouseX, &mouseY);
            ImGui::Text("mouse x: %i, y: %i", mouseX, mouseY);
            ImGui::Checkbox("Hit Box", &hb);

            std::string entityTag = editorSystem.entityTag;

            ImGui::Text("Entity Tag: %s", entityTag.c_str());
            ImGui::Text("Entity ID: %i", registry->GetSystem<EditorSystem>().entityID);

        }
        ImGui::End();

    }

//    void EDITOR::MouseDisplay::MousePressed(std::shared_ptr<Registry>& registry)
//    {
//        auto editorSystem = registry->GetSystem<EditorSystem>();
//        for (auto entity: editorSystem.GetSystemEntities())
//        {
//            // Works!
////                std::cout << entity.GetId() << std::endl;
//            int x = entity.GetComponent<TransformComponent>().position.x;
//            int y = entity.GetComponent<TransformComponent>().position.y;
//            int w = entity.GetComponent<BoxColliderComponent>().width;
//            int h = entity.GetComponent<BoxColliderComponent>().height;
//
//            if (mouseX > x && mouseX < (x + w) && mouseY > y && mouseY < (y + h))
//            {
//                hitBox = true;
//            }
//            else
//                hitBox = false;
//
//        }
//
//    }

} // end namespace