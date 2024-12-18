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
 * @brief Movement system for all entities.
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

            // Apply the velocity
            transform.position.x += (rigidBody.velocity.x * deltaTime);
            transform.position.y += (rigidBody.velocity.y) * deltaTime;

            // Reset the transform position for top-left
            if (transform.position.x < 0) transform.position.x = 0;
            if (transform.position.y < 0) transform.position.y = 0;

        }
    }
};

#endif //RETRO_ENGINE_MOVEMENTSYSTEM_H
