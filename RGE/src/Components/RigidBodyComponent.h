#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

struct RigidBodyComponent
{
    glm::vec2 velocity = glm::vec2(0.0, 0.0);
    glm::vec2 delta = glm::vec2(0.0, 0.0);
    float speed = 50.0f;
    float gravity = 1.5f;
    float jumpForce = 2.0f;
    float velocityMultiplier = 0.2f;

    [[nodiscard]] float getSpeed() const { return speed; }

    void setSpeed(float _speed) { this->speed = _speed; }

    explicit RigidBodyComponent(glm::vec2 _velocity = glm::vec2(0.0, 0.0)) { this->velocity = _velocity; }
};

#endif
