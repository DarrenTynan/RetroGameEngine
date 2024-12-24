#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>
#include "../../RGE/src/FSM/include/FSM.h"

//@export var speed = 232
//@export var jump_speed = -800
//@export var gravity = 300 *  9.8
//
//@export_range(0.0, 1.0) var friction = 0.32
//@export_range(0.0 , 1.0) var acceleration = 0.32
//
//var is_jumping :bool= false

struct RigidBodyComponent
{
    FSM* fsm = new FSM();

    glm::vec2 velocity = glm::vec2(0.0, 0.0);
    float speed = 80.0f;
    float gravityForce = -9.81f;
    float jumpHeight = 3.5;
    float timeToJumpApex = 0.4f;
    float jumpForce = 0.2f;

    explicit RigidBodyComponent(glm::vec2 _velocity = glm::vec2(0.0, 0.0))
    {
        this->velocity = _velocity;
    }
};

#endif
