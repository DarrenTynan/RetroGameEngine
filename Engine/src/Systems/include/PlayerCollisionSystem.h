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

        bool isCollisionX = false;
        bool isCollisionY = false;

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

                SDL_Rect aa = {
                        (int) aTransform.position.x,
                        (int) aTransform.position.y,
                        (int) aCollider.width * (int) aTransform.scale.x,
                        (int) aCollider.height * (int) aTransform.scale.y
                };

                SDL_Rect bb = {
                        (int) bTransform.position.x,
                        (int) bTransform.position.y,
                        (int) bCollider.width * (int) bTransform.scale.x,
                        (int) bCollider.height * (int) bTransform.scale.y
                };

                // Down
                SDL_Rect downCast = {
                        (int) (aTransform.position.x + aCollider.width / 2),
                        (int) (aTransform.position.y + aCollider.height),
                        1,
                        10
                };

                // Perform the AABB collision check between entities a and b
                SDL_bool isCollision = SDL_HasIntersection(&aa, &bb);

                if (isCollision)
                {

                    SDL_bool isDownCast = SDL_HasIntersection(&downCast, &bb);
                    if (isDownCast)
                    {
//                        std::cout << "Cast Down Hit" << std::endl;
                        aRB.fsm->isGrounded = true;
                    }

//                    IntersectRect(aa, bb);

                    // Now we know there is a collision we need to find out the value of intersection.

                    // Down collision
                    if ((aRB.fsm->direction.y > 0 && (aa.y + aa.h) > bb.y) && !isCollisionX)
                    {
                        std::cout << "Down: " << (aa.y + aa.h) - bb.y << std::endl;
                        isCollisionY = true;
                    }

                    // Up collision
                    if ((aRB.fsm->direction.y < 0 && aa.y < (bb.y + bb.h)) && !isCollisionX)
                    {
                        std::cout << "Up: " << (bb.y + bb.h) - aa.y << std::endl;
                        isCollisionY = true;
                    }

                    // Right collision
                    if ((aRB.fsm->direction.x > 0 && (aa.x + aa.w) > bb.x) && !isCollisionY)
                    {
                        std::cout << "Right: " << (aa.x + aa.w) - bb.x << std::endl;
                        isCollisionX = true;
                    }

                    // Left collision
                    if ((aRB.fsm->direction.x < 0 && aa.x < (bb.x + bb.w)) && !isCollisionY)
                    {
                        std::cout << "Left: " << (bb.x + bb.w) - aa.x << std::endl;
                        isCollisionX = true;
                    }

                    // TODO up left right
                    // TODO down left right

                    // Left
                    if (isCollisionX && aRB.fsm->direction.x < 0)
                    {
                        aTransform.position.x = (float) (bb.x + bb.w) ;
                        aRB.deltaXY.x = 0;
                        aRB.fsm->direction.x = 0;
                        break;
                    }

                    // Right
                    if (isCollisionX && aRB.fsm->direction.x > 0)
                    {
                        aTransform.position.x = (float) (bb.x - aa.w);
                        aRB.deltaXY.x = 0;
                        aRB.fsm->direction.x = 0;
                        break;
                    }

                    // Up
                    if (isCollisionY && aRB.fsm->direction.y < 0)
                    {
                        aTransform.position.y = (float) (bb.y + bb.h);
                        aRB.deltaXY.y = 0;
                        aRB.fsm->direction.y = 0;
                        break;
                    }

                    // Down
                    if (isCollisionY && aRB.fsm->direction.y > 0)
                    {
                        aTransform.position.y = (float) (bb.y - aa.h);
                        aRB.deltaXY.y = 0;
                        aRB.fsm->direction.y = 0;
                        break;
                    }
                }
            }
        }

        /**
         * @brief Debug display.
         *
         * @param aa
         * @param bb
         */
        void IntersectRect(SDL_Rect &aa, SDL_Rect &bb)
        {
            SDL_Rect cc;
            SDL_IntersectRect(&aa, &bb, &cc);

            std::cout << "Box aa.x: " << aa.x << std::endl;
            std::cout << "Box aa.y: " << aa.y << std::endl;
            std::cout << "Box aa.w: " << aa.w << std::endl;
            std::cout << "Box aa.h: " << aa.h << std::endl;

            std::cout << "Box bb.x: " << bb.x << std::endl;
            std::cout << "Box bb.y: " << bb.y << std::endl;
            std::cout << "Box bb.w: " << bb.w << std::endl;
            std::cout << "Box bb.h: " << bb.h << std::endl;

            std::cout << "Box cc.x: " << cc.x << std::endl;
            std::cout << "Box cc.y: " << cc.y << std::endl;
            std::cout << "Box cc.w: " << cc.w << std::endl;
            std::cout << "Box cc.h: " << cc.h << std::endl;

            std::cout << "**********" << std::endl;
        }
    };

} // end namespace

#endif //RETROGAMEENGINE_PLAYERCOLLISIONSYSTEM_H
