#ifndef PLAYERCONTROLLEDCOMPONENT_H
#define PLAYERCONTROLLEDCOMPONENT_H

#include <glm/glm.hpp>

struct PlayerControllerComponent
{
    glm::vec2 upVelocity{};
    glm::vec2 rightVelocity{};
    glm::vec2 downVelocity{};
    glm::vec2 leftVelocity{};
    glm::vec2 idleVelocity = glm::vec2(0);

    /**
     * @brief A small struct to hold the vec2 velocities.
     *
     * @param upVelocity
     * @param rightVelocity
     * @param downVelocity
     * @param leftVelocity
     */
    explicit PlayerControllerComponent(glm::vec2 upVelocity = glm::vec2(0), glm::vec2 rightVelocity = glm::vec2(0), glm::vec2 downVelocity = glm::vec2(0), glm::vec2 leftVelocity = glm::vec2(0)) {
        this->upVelocity = upVelocity;
        this->rightVelocity = rightVelocity;
        this->downVelocity = downVelocity;
        this->leftVelocity = leftVelocity;
    }
};

#endif
