#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>
#include <utility>

namespace RGE_Component
{

/**
 * @brief A small struct to hold the box collider vars
 *
 * @param int width
 * @param int height
 * @param vec2 position
 */
struct BoxColliderComponent
{
    float width;
    float height;
    glm::vec2 position{};
    bool hasRaycast;

    explicit BoxColliderComponent(float _width = 0.0f, float _height = 0.0f, glm::vec2 _position = glm::vec2(0,0), bool _hasRaycast = false)
    {
        this->width = _width;
        this->height = _height;
        this->position = _position;
        this->hasRaycast = _hasRaycast;
    }
};

} // end namespace

#endif
