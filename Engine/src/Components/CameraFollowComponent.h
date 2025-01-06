#ifndef CAMERAFOLLOWCOMPONENT_H
#define CAMERAFOLLOWCOMPONENT_H

#include <glm/glm.hpp>

struct CameraFollowComponent
{
    float cameraWidth;
    float cameraHeight;
    glm::vec2 position{};


//    explicit CameraFollowComponent(SDL_Rect _gameCamera)
    explicit CameraFollowComponent()
    {
        position.x = 100.0f;
        position.y = 50.0f;
        cameraWidth = 400.0f;   //width;
        cameraHeight = 200.0f;  //height;

    }
};

#endif
