#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>
#include "../../RGE/src/FSM/include/FSM.h"

struct RigidBodyComponent
{
    FSM* fsm = new FSM();

    glm::vec2 velocity = glm::vec2(0.0, 0.0);
    float speed = 50.0f;
    float gravityForce = 2.0f;
    float jumpForce = 100.0f;

    [[nodiscard]] float getSpeed() const { return speed; }

    void setSpeed(float _speed) { this->speed = _speed; }

    explicit RigidBodyComponent(glm::vec2 _velocity = glm::vec2(0.0, 0.0)) { this->velocity = _velocity; }
};

#endif
