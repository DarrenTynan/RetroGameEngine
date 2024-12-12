#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>
#include <utility>

/**
 * @brief A small struct to hold the box collider vars
 *
 * @param int width
 * @param int height
 * @param vec2 offset
 * @param string name
 */
struct BoxColliderComponent
{
    int width;
    int height;
    glm::vec2 offset{};
    std::string name;

    explicit BoxColliderComponent(int width = 0, int height = 0,  glm::vec2 offset = glm::vec2(0,0))
    {
        this->width = width;
        this->height = height;
        this->offset = offset;
    }

    void addName(std::string _name = "default")
    {
        this->name = std::move(_name);
    }
};

#endif
