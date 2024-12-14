//
// Created by Darren Tynan on 27/12/2022.
//

#ifndef RETRO_ENGINE_MOVEMENTSYSTEM_H
#define RETRO_ENGINE_MOVEMENTSYSTEM_H

#include "../ECS/include/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../ECS/include/Registry.h"

/**
 * @brief Movement system
 */
class MovementSystem: public System
{
public:
    MovementSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    // Update position during Delta Time
    void Update(double deltaTime)
    {
        // Check all entities.
        for (auto entity: GetSystemEntities())
        {
            auto& transform = entity.GetComponent<TransformComponent>();
            auto rigidBody = entity.GetComponent<RigidBodyComponent>();

            float gravity = 0;
            if (entity.HasTag("player") && !rigidBody.isGrounded)
            {
                gravity = rigidBody.gravity;

//                Logger::Log("Entity id = " + std::to_string(entity.GetId()) +
//                " position is now (" + std::to_string(transform.position.x) +
//                ", " + std::to_string(transform.position.y));
            }

//            if (entity.HasTag("player") && rigidBody.isGrounded)
//            {
//                gravity = -40.0;
//            }

            // Apply the velocity
            transform.position.x += (rigidBody.velocity.x * deltaTime);
            transform.position.y += (rigidBody.velocity.y + gravity) * deltaTime;


            // Reset the transform position.
            if (transform.position.x < 0) transform.position.x = 0;
            if (transform.position.y < 0) transform.position.y = 0;

        }
    }
};

#endif //RETRO_ENGINE_MOVEMENTSYSTEM_H
