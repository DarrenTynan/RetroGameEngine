//
// Created by Darren Tynan on 18/03/2025.
//

#ifndef RETROGAMEENGINE_PLAYERCOLLISIONSYSTEM_H
#define RETROGAMEENGINE_PLAYERCOLLISIONSYSTEM_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_rect.h>

#include "../../ECS/include/ECS.h"
#include "../../EventBus/include/EventBus.h"
#include "../../Events/include/CollisionEvent.h"
#include "../../Components/include/BoxColliderComponent.h"
#include "../../Components/include/TransformComponent.h"

namespace RGE_System
{

    /**
     * @brief Bounding box collision between the player box collider and other box colliders. ie. ground
     */
    class PlayerCollisionSystem: public System
    {
    public:
        PlayerCollisionSystem()
        {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }

        // Check entity bounding box for collision.
        void Update(std::unique_ptr<EventBus>& eventBus, std::shared_ptr<Registry>& registry)
        {
            auto a = registry->GetEntityByTag("player");
            auto &aTransform = a.GetComponent<TransformComponent>();
            auto &aCollider = a.GetComponent<BoxColliderComponent>();
            auto &aRB = a.GetComponent<RigidBodyComponent>();

            auto entities = GetSystemEntities();

            // Loop all the entities that the system is interested in
            for (auto i = entities.begin(); i != entities.end(); i++)
            {
                Entity b = *i;

                // Bypass if we are trying to test the same entity
                if (a == b)
                    continue;

                auto &bTransform = b.GetComponent<TransformComponent>();
                auto &bCollider = b.GetComponent<BoxColliderComponent>();

                SDL_Rect aa;
                aa.x = (int) aTransform.position.x;
                aa.y = (int) aTransform.position.y;
                aa.w = (int) aCollider.width * (int) aTransform.scale.x;
                aa.h = (int) aCollider.height * (int) aTransform.scale.y;

                SDL_Rect bb;
                bb.x = (int) bTransform.position.x;
                bb.y = (int) bTransform.position.y;
                bb.w = (int) bCollider.width * (int) bTransform.scale.x;
                bb.h = (int) bCollider.height * (int) bTransform.scale.y;

                // Perform the AABB collision check between entities a and b
                SDL_bool isCollision = SDL_HasIntersection(&aa, &bb);

                if (isCollision)
                {
//                    std::cout << "Box aa.x: " << aa.x << std::endl;
//                    std::cout << "Box aa.y: " << aa.y << std::endl;
//                    std::cout << "Box aa.w: " << aa.w << std::endl;
//                    std::cout << "Box aa.h: " << aa.h << std::endl;

//                    std::cout << "Box bb.x: " << bb.x << std::endl;
//                    std::cout << "Box bb.y: " << bb.y << std::endl;
//                    std::cout << "Box bb.w: " << bb.w << std::endl;
//                    std::cout << "Box bb.h: " << bb.h << std::endl;

                    if (aRB.fsm->direction.x < 0)
                    {
                        aTransform.position.x = (float)(bb.x + bb.w);
                        aRB.deltaXY = glm::vec2 (0,0);
                        aRB.fsm->direction = glm::vec2 (0,0);
                        break;
                    }

                    else if (aRB.fsm->direction.x > 0)
                    {
                        aTransform.position.x = (float)(bb.x - aCollider.width);
                        aRB.deltaXY = glm::vec2 (0,0);
                        aRB.fsm->direction = glm::vec2 (0,0);
                        break;
                    }

                    else if (aRB.fsm->direction.y < 0)
                    {
                        aTransform.position.y = (float)(bb.y + bb.h);
                        aRB.deltaXY = glm::vec2 (0,0);
                        aRB.fsm->direction = glm::vec2 (0,0);
                        break;
                    }

                    else if (aRB.fsm->direction.y > 0)
                    {
                        aTransform.position.y = (float)(bb.y - aa.h);
                        aRB.deltaXY = glm::vec2 (0,0);
                        aRB.fsm->direction = glm::vec2 (0,0);
                        break;
                    }
                }
            }
        }
    };

} // end namespace

#endif //RETROGAMEENGINE_PLAYERCOLLISIONSYSTEM_H
