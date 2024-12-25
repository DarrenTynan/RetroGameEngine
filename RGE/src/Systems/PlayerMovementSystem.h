//
// Created by Darren Tynan on 23/12/2024.
//

#ifndef RETROGAMEENGINE_PLAYERMOVEMENTSYSTEM_H
#define RETROGAMEENGINE_PLAYERMOVEMENTSYSTEM_H

//#include "Globals.h"
#include "../ECS/include/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../ECS/include/Registry.h"
#include <math.h>

/**
 * @brief Movement system for all entities.
 */

class PlayerMovementSystem: public System
{
public:
    PlayerMovementSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    // Update position during Delta Time
    static void Update(const std::unique_ptr<Registry>& registry, double deltaTime)
    {

        Entity player = registry->GetEntityByTag("player");

        auto &transform = player.GetComponent<TransformComponent>();
        auto rigidBody = player.GetComponent<RigidBodyComponent>();

        // NOT NEEDED ANYMORE -  Kinematics - Apply the velocity
//        transform.position.x += rigidBody.velocity.x * rigidBody.speed * deltaTime;
//        transform.position.y += rigidBody.velocity.y * rigidBody.speed * deltaTime;


        if (!rigidBody.fsm->isGrounded)
            rigidBody.velocity.y += 2.0f;

        // Change position based on velocity.
        transform.position.x += rigidBody.velocity.x;
        transform.position.y += rigidBody.velocity.y;
    }
};

#endif //RETROGAMEENGINE_PLAYERMOVEMENTSYSTEM_H
