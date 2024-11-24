#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

struct RigidBodyComponent {
    glm::vec2 velocity;
    glm::vec2 delta = glm::vec2(0.0, 0.0);
    glm::vec2 direction = glm::vec2 (0.0,0.0);
    float speed = 74;
    float gravity = 1.5;

    RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0)) {
        this->velocity = velocity;
    }
};

#endif
