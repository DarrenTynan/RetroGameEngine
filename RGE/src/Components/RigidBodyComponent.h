#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>
#include "../../RGE/src/FSM/include/FSM.h"

struct RigidBodyComponent
{
    FSM* fsm = new FSM();

    glm::vec2 velocity = glm::vec2(0.0, 0.0);
    float speed = 0.02f;
    float gravityForce = -9.81f;
    float jumpHeight = 3.5;
    float timeToJumpApex = 0.4f;
    float jumpForce = 0.2f;

    [[nodiscard]] float getSpeed() const { return speed; }

    void setSpeed(float _speed) { this->speed = _speed; }

    explicit RigidBodyComponent(glm::vec2 _velocity = glm::vec2(0.0, 0.0)) { this->velocity = _velocity; }
};

#endif
