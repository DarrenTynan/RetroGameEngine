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
    int cameraOffsetX;
    int cameraOffsetY;
    SDL_Rect frustum = {
            0,
            0,
            400,
            200
    };

    /**
     *
     * @brief Camera follow struct.
     *
     * @param _tileCountX
     * @param _tileCountY
     * @param _tileSize
     * @param _cameraOffsetX
     * @param _cameraOffsetY
     */
    explicit CameraFollowComponent(int _tileCountX = 0, int _tileCountY = 0, int _tileSize = 0, int _cameraOffsetX = 0, int _cameraOffsetY = 0)
    {
        this->tileCountX = _tileCountX;
        this->tileCountY = _tileCountY;
        this->tileSize = _tileSize;
        this->cameraOffsetX = _cameraOffsetX;
        this->cameraOffsetY = _cameraOffsetY;
        frustum.x = (_cameraOffsetX + (_tileSize / 2)) - frustum.w / 2;
        frustum.y = (_cameraOffsetY + (_tileSize / 2)) - frustum.h / 2;
    }
};

} // end namespace
#endif //CAMERAFOLLOWCOMPONENT_H
