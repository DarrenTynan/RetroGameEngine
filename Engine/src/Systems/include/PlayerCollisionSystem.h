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
        void Update(std::unique_ptr<EventBus>& eventBus, std::shared_ptr<Registry>& registry, SDL_Rect camera)
        {
            auto a = registry->GetEntityByTag("player");
            auto &aTransform = a.GetComponent<TransformComponent>();
            auto &aCollider = a.GetComponent<BoxColliderComponent>();
            auto &aRB = a.GetComponent<RigidBodyComponent>();
            auto &aSprite = a.GetComponent<SpriteComponent>();
            auto &fsmComponent = a.GetComponent<FSMComponent>();
            auto fsm = fsmComponent.getFsm();

            int x1, y1, x2, y2;

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

                // Perform the AABB collision check between entities a and b
                SDL_bool isCollision = SDL_HasIntersection(&aa, &bb);

                /**
                 * @brief Check ray-cast intersections.
                 */
                x1 = (int)(aTransform.position.x + aCollider.width / 2);
                y1 = (int)(aTransform.position.y);
                x2 = (int)(aTransform.position.x + aCollider.width / 2);
                y2 = (int)(aTransform.position.y - aCollider.rayLength);
                SDL_bool isUpRayCast = SDL_IntersectRectAndLine(&bb, &x1, &y1, &x2, &y2);

                x1 = (int)(aTransform.position.x);
                y1 = (int)(aTransform.position.y + aCollider.height / 2);
                x2 = (int)(aTransform.position.x - aCollider.rayLength);
                y2 = (int)(aTransform.position.y + aCollider.height / 2);
                SDL_bool isLeftRayCast = SDL_IntersectRectAndLine(&bb, &x1, &y1, &x2, &y2);

                x1 = (int)(aTransform.position.x + aCollider.width / 2);
                y1 = (int)(aTransform.position.y + aCollider.height);
                x2 = (int)(aTransform.position.x + aCollider.width / 2);
                y2 = (int)(aTransform.position.y + aCollider.height + aCollider.rayLength);
                SDL_bool isDownRayCast = SDL_IntersectRectAndLine(&bb, &x1, &y1, &x2, &y2);

                x1 = (int)(aTransform.position.x + aCollider.width);
                y1 = (int)(aTransform.position.y + aCollider.height / 2);
                x2 = (int)((aTransform.position.x + aCollider.width) + aCollider.rayLength);
                y2 = (int)(aTransform.position.y + aCollider.height / 2);
                SDL_bool isRightRayCast = SDL_IntersectRectAndLine(&bb, &x1, &y1, &x2, &y2);


                /**
                 * @brief Check the ray-cast flags.
                 */
                if (isUpRayCast || isRightRayCast || isDownRayCast || isLeftRayCast)
                {
                    // Now we know there is a collision we need to find out the value of intersection.
                    SDL_Rect cc = IntersectRect(aa, bb);

                    // Up
                    if (isUpRayCast)
                    {
                        aTransform.position.y += (float)cc.h + aCollider.rayLength;
                        aRB.deltaXY.y = 0;
                        fsm->direction.y = 0;

                        break;
                    }

                    // Right
                    if (isRightRayCast)
                    {
                        std::cout << bCollider.name << std::endl;
                        aTransform.position.x += (float)cc.w - aCollider.rayLength;
                        aRB.deltaXY.x = 0;
                        fsm->direction.x = 0;
                        break;
                    }

                    // Down
                    if (isDownRayCast)
                    {

                        aTransform.position.y -= (float)cc.h + aCollider.rayLength;
                        aRB.deltaXY.y = 0;
                        fsm->direction.y = 0;

                        fsm->isGrounded = true;
                        break;
                    }

                    // Left
                    if (isLeftRayCast)
                    {
                        aTransform.position.x -= (float)cc.w - aCollider.rayLength;
                        aRB.deltaXY.x = 0;
                        fsm->direction.x = 0;
                        break;
                    }

                } else fsm->isGrounded = false;
            }
        }


        /**
         * @brief Debug display.
         *
         * @param aa
         * @param bb
         */
        static SDL_Rect IntersectRect(SDL_Rect &aa, SDL_Rect &bb)
        {
            SDL_Rect cc;
            SDL_IntersectRect(&aa, &bb, &cc);

//            std::cout << "Box aa.x: " << aa.x << std::endl;
//            std::cout << "Box aa.y: " << aa.y << std::endl;
//            std::cout << "Box aa.w: " << aa.w << std::endl;
//            std::cout << "Box aa.h: " << aa.h << std::endl;
//
//            std::cout << "Box bb.x: " << bb.x << std::endl;
//            std::cout << "Box bb.y: " << bb.y << std::endl;
//            std::cout << "Box bb.w: " << bb.w << std::endl;
//            std::cout << "Box bb.h: " << bb.h << std::endl;
//
//            std::cout << "Box cc.x: " << cc.x << std::endl;
//            std::cout << "Box cc.y: " << cc.y << std::endl;
//            std::cout << "Box cc.w: " << cc.w << std::endl;
//            std::cout << "Box cc.h: " << cc.h << std::endl;
//
//            std::cout << "**********" << std::endl;

            return cc;
        }
    };

} // end namespace

#endif //RETROGAMEENGINE_PLAYERCOLLISIONSYSTEM_H
