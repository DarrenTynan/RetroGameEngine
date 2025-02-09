//
// Created by Darren Tynan on 27/12/2022.
//

#ifndef RETRO_ENGINE_MOVEMENTSYSTEM_H
#define RETRO_ENGINE_MOVEMENTSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../Components/include/TransformComponent.h"
#include "../../Components/include/RigidBodyComponent.h"
#include "../../ECS/include/Registry.h"

namespace RGE_System
{

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
            // We are not going to apply forces to player.
            if (entity.HasTag("player"))
            {
                continue;
            }

            auto& transform = entity.GetComponent<TransformComponent>();
            auto rigidBody = entity.GetComponent<RigidBodyComponent>();

            // Apply the velocityDelta
            transform.position.x += (rigidBody.velocityDelta.x * deltaTime);
            transform.position.y += (rigidBody.velocityDelta.y * deltaTime);

        }
    }
};

} // end namespace
#endif //RETRO_ENGINE_MOVEMENTSYSTEM_H
