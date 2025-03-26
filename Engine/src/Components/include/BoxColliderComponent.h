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
    // Center is not used atm.
    glm::vec2 center{};

    bool hasRaycast;
    float rayLength = 5.0f;
    glm::vec4 upCast{};
    glm::vec4 rightCast{};
    glm::vec4 downCast{};
    glm::vec4 leftCast{};

    explicit BoxColliderComponent(float _width = 0.0f, float _height = 0.0f, glm::vec2 _center = glm::vec2(0,0), bool _hasRaycast = false)
    {
        this->width = _width;
        this->height = _height;
        this->center = _center;
        this->hasRaycast = _hasRaycast;
    }
};

} // end namespace

#endif
