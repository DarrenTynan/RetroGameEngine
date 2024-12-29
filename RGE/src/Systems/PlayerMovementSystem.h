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
    static void Update(double deltaTime)
    {
        extern std::unique_ptr<Registry> g_registry;
        Entity player = g_registry->GetEntityByTag("player");

        auto &transform = player.GetComponent<TransformComponent>();
        auto &rigidBody = player.GetComponent<RigidBodyComponent>();

        // Save the current velocity
//        rigidBody.oldVelocity = rigidBody.velocity;
//        glm::vec2 v2(0.0, 0.0);
//        v2.x = rigidBody.oldVelocity.x + rigidBody.acceleration * (float)deltaTime;
//        v2.y = rigidBody.oldVelocity.y + rigidBody.acceleration * (float)deltaTime;
//        rigidBody.velocity = v2;

        // NOT NEEDED ANYMORE -  Kinematics - Apply the velocity
//        transform.position.x += rigidBody.velocity.x * rigidBody.speed * deltaTime;
//        transform.position.y += rigidBody.velocity.y * rigidBody.speed * deltaTime;

        // Add gravity
        if (!rigidBody.fsm->isGrounded)
        {
            rigidBody.fsm->toggleTest();
            rigidBody.fsm->isGrounded = false;
            rigidBody.fsm->direction.y = 1;
            rigidBody.velocity.y += rigidBody.gravity * deltaTime;

            if (rigidBody.velocity.y > rigidBody.maxGravity)
                rigidBody.velocity.y = rigidBody.maxGravity;
        }

        // Change position based on the new velocity + force.
        transform.position.x += rigidBody.velocity.x;// * deltaTime;
        transform.position.y += rigidBody.velocity.y;// * deltaTime;
    }

};

#endif //RETROGAMEENGINE_PLAYERMOVEMENTSYSTEM_H
