#ifndef PLAYERCONTROLLEDCOMPONENT_H
#define PLAYERCONTROLLEDCOMPONENT_H

#include <glm/glm.hpp>

struct PlayerControllerComponent {
    glm::vec2 upVelocity;
    glm::vec2 rightVelocity;
    glm::vec2 downVelocity;
    glm::vec2 leftVelocity;
    glm::vec2 idleVelocity = glm::vec2(0);

    PlayerControllerComponent(glm::vec2 upVelocity = glm::vec2(0), glm::vec2 rightVelocity = glm::vec2(0), glm::vec2 downVelocity = glm::vec2(0), glm::vec2 leftVelocity = glm::vec2(0)) {
        this->upVelocity = upVelocity;
        this->rightVelocity = rightVelocity;
        this->downVelocity = downVelocity;
        this->leftVelocity = leftVelocity;
    }
};

#endif
