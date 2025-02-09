//
// Created by Darren Tynan on 23/12/2024.
//

#ifndef RETROGAMEENGINE_PLAYERCONTROLLERSYSTEM_H
#define RETROGAMEENGINE_PLAYERCONTROLLERSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../Components/include/TransformComponent.h"
#include "../../Components/include/RigidBodyComponent.h"
#include "../../ECS/include/Registry.h"
#include <cmath>

namespace RGE_System
{

/**
 * @brief Movement system for all entities.
 */

class PlayerControllerSystem: public System
{
public:
    PlayerControllerSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    // Update position during Delta Time
    // player.dy += gravity
    // player.dx *= friction
    //
    // Key check:
    //  player.dx -=/+= acceleration
    //
    // Limit speed
    //
    // Apply DX:
    //  player.x += dx, player.y += dy
    //
    // Ground collision
    //
    // Check screen bounds
    static void Update(std::unique_ptr<Registry>& registry, double deltaTime)
    {
        Entity player = registry->GetEntityByTag("player");

        auto &transform = player.GetComponent<TransformComponent>();
        auto &rigidBody = player.GetComponent<RigidBodyComponent>();

        // 1
//        rigidBody.velocityDelta.y += rigidBody.gravity;
        rigidBody.velocityDelta.x *= rigidBody.friction;

        // 2
        // TODO button check

        /* Poll for events. SDL_PollEvent() returns 0 when there are no  */
        /* more events on the event queue, our while loop will exit when */
        /* that occurs.                                                  */


        // 3
        // Limit speed

        // 4
        transform.position.x += rigidBody.velocityDelta.x;
        transform.position.y += rigidBody.velocityDelta.y;

//            // Add gravity
//        if (!rigidBody.fsm->isGrounded)
//        {
////            rigidBody.fsm->toggleTest();
//            rigidBody.fsm->isGrounded = false;
//            rigidBody.fsm->direction.y = 1;
//            rigidBody.velocityDelta.y += rigidBody.gravity * deltaTime;
//        }
//
//        // Change position based on the new velocityDelta + force.
//        transform.position.x += rigidBody.velocityDelta.x *= rigidBody.friction;
//        transform.position.y += rigidBody.velocityDelta.y;// * deltaTime;
    }

};

} // end namespace
#endif //RETROGAMEENGINE_PLAYERCONTROLLERSYSTEM_H
