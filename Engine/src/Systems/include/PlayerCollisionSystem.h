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
                 * @brief There is a collision!
                 */
//                if (isCollision)
//                {
                    float rayLength = 5.0f;

                    // ray up
                    int x1u = (int)(aTransform.position.x + aCollider.width / 2);
                    int y1u = (int)(aTransform.position.y + aCollider.height + rayLength);
                    int x2u = (int)(aTransform.position.x + aCollider.width / 2);
                    int y2u = (int)(aTransform.position.y + aCollider.height);
                    SDL_bool isUpRayCast = SDL_IntersectRectAndLine(&bb, &x1u, &y1u, &x2u, &y2u);

//                    if (isUpRayCast)
//                        std::cout << "isUpRayCast" << std::endl;

                    // ray right
                    int x1r = (int)(aTransform.position.x + aCollider.width);
                    int y1r = (int)(aTransform.position.y + aCollider.height / 2);
                    int x2r = (int)(aTransform.position.x + aCollider.width + rayLength);
                    int y2r = (int)(aTransform.position.y + aCollider.height / 2);
                    SDL_bool isRightRayCast = SDL_IntersectRectAndLine(&bb, &x1r, &y1r, &x2r, &y2r);

//                    if (isRightRayCast)
//                        std::cout << "isRightRayCast" << std::endl;

                    // ray down
                    int x1d = (int)(aTransform.position.x + aCollider.width / 2);
                    int y1d = (int)(aTransform.position.y + aCollider.height);
                    int x2d = (int)(aTransform.position.x + aCollider.width / 2);
                    int y2d = (int)(aTransform.position.y + aCollider.height + rayLength);
                    SDL_bool isDownRayCast = SDL_IntersectRectAndLine(&bb, &x1d, &y1d, &x2d, &y2d);

//                    if (isDownRayCast)
//                        std::cout << "isDownRayCast" << std::endl;

                    // ray left
                    int x1l = (int)(aTransform.position.x);
                    int y1l = (int)(aTransform.position.y + aCollider.height / 2);
                    int x2l = (int)(aTransform.position.x - rayLength);
                    int y2l = (int)(aTransform.position.y + aCollider.height / 2);
                    SDL_bool isLeftRayCast = SDL_IntersectRectAndLine(&bb, &x1l, &y1l, &x2l, &y2l);

//                    if (isLeftRayCast)
//                        std::cout << "isLeftRayCast" << std::endl;

                if (isUpRayCast || isRightRayCast || isDownRayCast || isLeftRayCast)
                {

//                    SDL_bool isDownCast = SDL_HasIntersection(&downCast, &bb);

//                    if (isDownCast)
//                    {
//                        std::cout << "Cast Down Hit" << std::endl;
//                        aRB.fsm->isGrounded = true;
//                    }
//                    else
//                        aRB.fsm->isGrounded = false;

                    // Now we know there is a collision we need to find out the value of intersection.
                    SDL_Rect cc = IntersectRect(aa, bb);

                    // Right
                    if (isRightRayCast)
                    {
                        aTransform.position.x = (float) (bb.x - aa.w);
                        aRB.deltaXY.x = 0;
                        aRB.fsm->direction.x = 0;
                        break;
                    }

                    // Down
                    if (isDownRayCast)
                    {
                        aRB.fsm->isGrounded = true;

                        aTransform.position.y -= (float)cc.h;
                        aRB.deltaXY.y = 0;
                        aRB.fsm->direction.y = 0;
                        break;
                    }

                    // Left
                    if (isLeftRayCast)
                    {
                        aTransform.position.x = (float) (bb.x + bb.w) ;
                        aRB.deltaXY.x = 0;
                        aRB.fsm->direction.x = 0;
                        break;
                    }

                } else aRB.fsm->isGrounded = false;
            }
        }

        /**
         * @brief Debug display.
         *
         * @param aa
         * @param bb
         */
        SDL_Rect IntersectRect(SDL_Rect &aa, SDL_Rect &bb)
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
