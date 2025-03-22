#ifndef CAMERAFOLLOWCOMPONENT_H
#define CAMERAFOLLOWCOMPONENT_H

#include <glm/glm.hpp>

namespace RGE_Component
{

struct CameraFollowComponent
{
    int tileCountX;
    int tileCountY;
    int tileSize;

    explicit CameraFollowComponent(int _tileCountX = 0, int _tileCountY = 0, int _tileSize = 0)
    {
        this->tileCountX = _tileCountX;
        this->tileCountY = _tileCountY;
        this->tileSize = _tileSize;
    }
};

} // end namespace
#endif //CAMERAFOLLOWCOMPONENT_H
