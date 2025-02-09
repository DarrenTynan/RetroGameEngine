#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>
#include "../../Engine/src/FSM/include/FSM.h"

namespace RGE_Component
{

/**
 * player.x is the number of pixels from the left that the player will start at.
 * player.y is the number of pixels from the top that the player will start at.
 * player.dx is the number of pixels that the player will move either left or right.
 * player.dy is the number of pixels that the player will move either up or down.
 * player.max_dx is the limit of how many pixels to allow the player to move left or right each frame.
 * player.max_dy is the limit of how many pixels to allow the player to move up or down each frame.
 * (We use the letter D before X and Y because in Mathematics we use the Greek letter "delta" to mean "change" or "how much something changes". So DX can be read as "how much X will change" or simply "change in X".)
 * player.acc (short for acceleration) is how much we add to DX when the player pushes the left or right buttons.
 * player.boost (jump power) is how much DY will suddenly decrease (making the player position higher) when the player pushes the jump button.
 * gravity (the force that constantly pulls "down") is how much DY will be increased every frame, all the time.
 * friction (the force that slows moving things down) is how much DX will be divided every frame, all the time.struct RigidBodyComponent
*/
struct RigidBodyComponent
{
    // Pointer to the Finite State Machine
    FSM* fsm = new FSM();

    // Velocity is the rate of change. DX and DY
    glm::vec2 velocityDelta = glm::vec2(0.0, 0.0);

    // maxVelocityDelta is the limit of how many pixels to allow the player to move each frame.
    glm::vec2 maxVelocityDelta = glm::vec2(2.0, 3.0);

    float acceleration = 1.5f;
    float jumpForce = 4.0f;
    float gravity = 0.3f;
    float friction = 0.85f;

    explicit RigidBodyComponent(glm::vec2 _velocity = glm::vec2(0.0, 0.0))
    {
        this->velocityDelta = _velocity;
    }
};

} // end namespace
#endif
