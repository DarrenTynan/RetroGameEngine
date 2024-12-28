#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>
#include "../../RGE/src/FSM/include/FSM.h"

struct RigidBodyComponent
{
    FSM* fsm = new FSM();

    glm::vec2 velocity = glm::vec2(0.0, 0.0);
    glm::vec2 oldVelocity = glm::vec2(0.0, 0.0);
//    glm::vec2 direction = glm::vec2(0.0, 0.0);

    float acceleration = 0.2f;
    float maxAcceleration = 1.0f;
    float speed = 3.0f;
    float gravity = 1.2f;

    float friction = 0.32f;
    float jumpHeight = 3.5f;
    float timeToJumpApex = 0.4f;
    float jumpForce = 0.2f;

    explicit RigidBodyComponent(glm::vec2 _velocity = glm::vec2(0.0, 0.0))
    {
        this->velocity = _velocity;
    }
};

#endif
