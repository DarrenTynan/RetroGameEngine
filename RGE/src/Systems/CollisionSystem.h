#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../ECS/include/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

/**
 * Bounding box collision between two rect's.
 */
class CollisionSystem: public System {
    public:
        CollisionSystem()
        {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }

        void Update(std::unique_ptr<EventBus>& eventBus)
        {
            auto entities = GetSystemEntities();

            // Loop all the entities that the system is interested in
            for (auto i = entities.begin(); i != entities.end(); i++)
            {
                Entity a = *i;
                auto aTransform = a.GetComponent<TransformComponent>();
                auto aCollider = a.GetComponent<BoxColliderComponent>();

                // Loop all the entities that still need to be checked (to the right of i)
                for (auto j = i; j != entities.end(); j++)
                {
                    Entity b = *j;

                    // Bypass if we are trying to test the same entity
                    if (a == b)
                    {
                        continue;
                    }

                    auto bTransform = b.GetComponent<TransformComponent>();
                    auto bCollider = b.GetComponent<BoxColliderComponent>();

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
                    SDL_bool collision = SDL_HasIntersection(&aa, &bb);

                    if (collision)
                    {
                        Logger::Log("Entity " + std::to_string(a.GetId()) +
                        " " + aCollider.name + " collided with entity " +
                        std::to_string(b.GetId()) + " " + bCollider.name);

                        auto& playerControllerComponent = a.GetComponent<PlayerControllerComponent>();
                        auto& playerRigidBodyComponent = a.GetComponent<RigidBodyComponent>();

//                        playerRigidBodyComponent.setSpeed(40.0f);
//                        playerRigidBodyComponent.setSpeed(74.0f);

                        if (playerRigidBodyComponent.direction.x != 0)
                        {
                            playerRigidBodyComponent.direction.x = playerRigidBodyComponent.direction.x * -1;
                            playerRigidBodyComponent.velocity.x = (playerRigidBodyComponent.speed * playerRigidBodyComponent.direction.x);
                        }

                        if (playerRigidBodyComponent.direction.y != 0)
                        {
                            playerRigidBodyComponent.direction.y = playerRigidBodyComponent.direction.y * -1;
                            playerRigidBodyComponent.velocity.y = (playerRigidBodyComponent.speed * playerRigidBodyComponent.direction.y);
                        }

//                        a.Kill();
//                        b.Kill();

                        eventBus->EmitEvent<CollisionEvent>(a, b);
                    }
                }
            }
        }

};

#endif
