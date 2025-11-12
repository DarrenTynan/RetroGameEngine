//
// Created by Darren Tynan on 21/04/2025.
//

#ifndef RETROGAMEENGINE_EDITORSYSTEM_H
#define RETROGAMEENGINE_EDITORSYSTEM_H

#include <rapidjson/document.h>
#include "include/Logger.h"
#include "../../ECS/include/ECS.h"
#include "../../Components/include/BoxColliderComponent.h"
#include "../../Components/include/ProjectileComponent.h"
#include "../../Components/include/HealthComponent.h"
#include "../../src/Components/include/TransformComponent.h"
#include "../../src/Components/include/RigidBodyComponent.h"

using namespace RGE_ECS;
// using namespace EDITOR_LOGGER;
using namespace RGE_Component;

namespace RGE_System
{
    class EditorSystem : public System
    {
    public:
        bool hitBox = false;
        int mouseX, mouseY, entityID;
        SDL_Event sdlEvent;
        std::string entityTag = "null";
        bool showBoxCollider = false;
        bool showGrid;
        SDL_Rect camera;

        EditorSystem() {};

        void lmbInFocus(std::shared_ptr<Registry> &registry, SDL_Renderer* renderer, SDL_Rect& _camera)
        {
            this->camera = _camera;

            SDL_GetMouseState(&mouseX, &mouseY);

            hitBox = false;
            auto editorSystem = registry->GetSystem<EditorSystem>();
            for (auto entity: editorSystem.GetSystemEntities())
            {
                int x = entity.GetComponent<TransformComponent>().position.x - camera.x;
                int y = entity.GetComponent<TransformComponent>().position.y - camera.y;
                int w = entity.GetComponent<BoxColliderComponent>().width;
                int h = entity.GetComponent<BoxColliderComponent>().height;

                if (mouseX > x && mouseX < (x + w) && mouseY > y && mouseY < (y + h))
                {
                    hitBox = true;
                    entityID = entity.GetId();
                    entityTag = registry->GetTagById(entityID);
                }


            }

        }


        void DrawGrid(SDL_Renderer *gameRenderer, int windowWidth, int windowHeight)
        {
            int x1 = 0;
            int y1 = 0;
            int x2 = windowWidth;
            int y2 = 0;
            SDL_SetRenderDrawColor(gameRenderer, 0xD3, 0xD3, 0xD3, 0xFF);

            // Horizontal
            for (int i = 0; i <= windowHeight / 32; ++i)
            {
                SDL_RenderDrawLine(gameRenderer, x1, y1, x2, y2);
                y1 = y1 + 32;
                y2 = y2 + 32;
            }

            x1 = 0;
            y1 = 0;
            x2 = 0;
            y2 = windowHeight;

            // Vertical
            for (int i = 0; i <= windowWidth / 32; ++i)
            {
                SDL_RenderDrawLine(gameRenderer, x1, y1, x2, y2);
                x1 = x1 + 32;
                x2 = x2 + 32;
            }

        }

    };

} // end namespace


#endif //RETROGAMEENGINE_EDITORSYSTEM_H
