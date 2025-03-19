//
// Created by Darren Tynan on 18/03/2025.
//

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

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
     * @brief Bounding box collision between two box collider rect's.
     * If a collision has happened to emit a signal (CollisionEvent)
     */
    class CollisionSystem: public System
    {
    public:
        CollisionSystem()
        {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }

        // Check entity bounding box for collision.
        void Update(std::unique_ptr<EventBus>& eventBus)
        {
            auto entities = GetSystemEntities();

            // Loop all the entities that the system is interested in
            for (auto i = entities.begin(); i != entities.end(); i++)
            {
                Entity a = *i;
                auto &aTransform = a.GetComponent<TransformComponent>();
                auto &aCollider = a.GetComponent<BoxColliderComponent>();
                auto &aRB = a.GetComponent<RigidBodyComponent>();

                // Loop all the entities that still need to be checked (to the right of i)
                for (auto j = i; j != entities.end(); j++)
                {
                    Entity b = *j;

                    // Bypass if we are trying to test the same entity
                    if (a == b)
                        continue;

                    auto &bTransform = b.GetComponent<TransformComponent>();
                    auto &bCollider = b.GetComponent<BoxColliderComponent>();
                    auto &bRB = a.GetComponent<RigidBodyComponent>();

                    SDL_Rect aa;
                    aa.x = (int)aTransform.position.x;
                    aa.y = (int)aTransform.position.y;
                    aa.w = (int)aCollider.width * (int)aTransform.scale.x;
                    aa.h = (int)aCollider.height * (int)aTransform.scale.y;

                    SDL_Rect bb;
                    bb.x = (int)bTransform.position.x;
                    bb.y = (int)bTransform.position.y;
                    bb.w = (int)bCollider.width * (int)bTransform.scale.x;
                    bb.h = (int)bCollider.height * (int)bTransform.scale.y;

                    // Perform the AABB collision check between entities a and b
                    SDL_bool isCollision = SDL_HasIntersection(&aa, &bb);

                    if (isCollision)
                        eventBus->EmitEvent<CollisionEvent>(a, b);
                }
            }
        }

    };

} // end namespace

#endif //COLLISIONSYSTEM_H
