#ifndef CAMERAFOLLOWCOMPONENT_H
#define CAMERAFOLLOWCOMPONENT_H

#include <glm/glm.hpp>

namespace RGE_Component
{

struct CameraFollowComponent
{
    float cameraWidth;
    float cameraHeight;
    glm::vec2 position{};

    explicit CameraFollowComponent()
    {
        position.x = 100.0f;
        position.y = 50.0f;
        cameraWidth = 400.0f;   //width;
        cameraHeight = 200.0f;  //height;

    }
};

} // end namespace
#endif
