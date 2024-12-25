#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>
#include "../../RGE/src/FSM/include/FSM.h"

struct RigidBodyComponent
{
    FSM* fsm = new FSM();

    glm::vec2 velocity = glm::vec2(0.0, 0.0);
    glm::vec2 oldVelocity = glm::vec2(0.0, 0.0);
    glm::vec2 direction = glm::vec2(0.0, 0.0);
    float dx = 0;
    float dy = 0;
    float maxDx = 2;
    float maxDy = 2;
    float acc = 05;
    float boost = 4;
    float grav = 0.3;
    float fric = 0.85;


    float acceleration = 0.32f;
    float speed = 80.0f;
    float friction = 0.32f;
    float gravityForce = -9.81f;
    float jumpHeight = 3.5f;
    float timeToJumpApex = 0.4f;
    float jumpForce = 0.2f;

    explicit RigidBodyComponent(glm::vec2 _velocity = glm::vec2(0.0, 0.0))
    {
        this->velocity = _velocity;
    }
};

#endif
