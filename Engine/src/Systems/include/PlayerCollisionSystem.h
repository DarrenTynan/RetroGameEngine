//
// Created by Darren Tynan on 18/03/2025.
//

#ifndef RETROGAMEENGINE_PLAYERCOLLISIONSYSTEM_H
#define RETROGAMEENGINE_PLAYERCOLLISIONSYSTEM_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

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
                    std::cout << "velocityDelta.x: " << aRB.velocityDelta.x << std::endl;
                    std::cout << "velocityDelta.y: " << aRB.velocityDelta.y << std::endl;
//                    std::cout << "PlayerCollisionSystem: Player has collided!" << std::endl;
//                    std::cout << "Box aa.x: " << aa.x << std::endl;
//                    std::cout << "Box aa.y: " << aa.y << std::endl;
//                    std::cout << "Box aa.w: " << aa.w << std::endl;
//                    std::cout << "Box aa.h: " << aa.h << std::endl;

//                    std::cout << "Box bb.x: " << bb.x << std::endl;
//                    std::cout << "Box bb.y: " << bb.y << std::endl;
//                    std::cout << "Box bb.w: " << bb.w << std::endl;
//                    std::cout << "Box bb.h: " << bb.h << std::endl;

                    // Horizontal
                    if (aRB.velocityDelta.x != 0)
                    {
                        // std::signbit determines if the given floating point number num is negative.
                        // true if num is negative, false otherwise.
                        if (std::signbit(aRB.velocityDelta.x))
                        {
                            std::cout << "Player walking left!" << std::endl;

                            aTransform.position.x = (float)(bb.x + bb.w);
                            break;
                        }

                        if (!std::signbit(aRB.velocityDelta.x))
                        {
                            std::cout << "Player walking right!" << std::endl;

                            aTransform.position.x = (float)(bb.x - aCollider.width);
                            aRB.velocityDelta.x = 0.0f;
                            aRB.velocityDelta.y = 0.0f;
                            break;
                        }
                        break;
                    }

                    // Vertical
                    if (aRB.velocityDelta.y != 0)
                    {
                        // std::signbit determines if the given floating point number num is negative.
                        // true if num is negative, false otherwise.
                        if (std::signbit(aRB.velocityDelta.y))
                        {
                            std::cout << "Player walking up!" << std::endl;
                            std::cout << "PRE aTransform.position.x: " << aTransform.position.x << std::endl;
                            std::cout << "PRE aTransform.position.y: " << aTransform.position.y << std::endl;
                            aTransform.position.y = (float)(bb.y + bb.h) + 1;
                            std::cout << "POST aTransform.position.x: " << aTransform.position.x << std::endl;
                            std::cout << "POST aTransform.position.y: " << aTransform.position.y << std::endl;
                            aRB.velocityDelta.x = 0.0f;
                            aRB.velocityDelta.y = 0.0f;
                            break;
                        }

                        if (!std::signbit(aRB.velocityDelta.y))
                        {
                            std::cout << "Player walking down!" << std::endl;
                            std::cout << "PRE aTransform.position.x: " << aTransform.position.x << std::endl;
                            std::cout << "PRE aTransform.position.y: " << aTransform.position.y << std::endl;
                            aTransform.position.y = (float)(bb.y - bb.h)-1;
                            std::cout << "POST aTransform.position.x: " << aTransform.position.x << std::endl;
                            std::cout << "POST aTransform.position.y: " << aTransform.position.y << std::endl;
                            aRB.velocityDelta.x = 0.0f;
                            aRB.velocityDelta.y = 0.0f;
                            break;
                        }
                    }
                }
            }
        }
    };

} // end namespace

#endif //RETROGAMEENGINE_PLAYERCOLLISIONSYSTEM_H
