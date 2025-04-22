//
// Created by Darren Tynan on 21/04/2025.
//

#ifndef RETROGAMEENGINE_EDITORSYSTEM_H
#define RETROGAMEENGINE_EDITORSYSTEM_H

#include "include/Logger.h"
#include "../../ECS/include/ECS.h"
#include "../../Components/include/BoxColliderComponent.h"
#include "../../Components/include/ProjectileComponent.h"
#include "../../Components/include/HealthComponent.h"
#include "../../src/Components/include/TransformComponent.h"
#include "../../src/Components/include/RigidBodyComponent.h"

using namespace RGE_ECS;
using namespace EDITOR_LOGGER;
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

        EditorSystem() {};

        void MousePressed(std::shared_ptr<Registry>& registry)
        {
            SDL_GetMouseState(&mouseX, &mouseY);

            hitBox = false;
            auto editorSystem = registry->GetSystem<EditorSystem>();
            for (auto entity: editorSystem.GetSystemEntities())
            {
                int x = entity.GetComponent<TransformComponent>().position.x;
                int y = entity.GetComponent<TransformComponent>().position.y;
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
    };

}
#endif //RETROGAMEENGINE_EDITORSYSTEM_H
