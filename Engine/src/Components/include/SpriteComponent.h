//
// SpriteComponent is used by all sprites including the tile set.
//

#ifndef RETROGAMEENGINE_SPRITECOMPONENT_H
#define RETROGAMEENGINE_SPRITECOMPONENT_H

#include <string>
#include <SDL2/SDL.h>

namespace RGE_Component
{

struct SpriteComponent
{
    std::string assetId;
    int width;
    int height;
    int zIndex;
    bool isFixed;
    SDL_Rect srcRect;
    bool flipH;

    /**
     * @brief SpriteComponent is used by all sprites including the tile set.
     *
     * @param _assetId
     * @param _width
     * @param _height
     * @param _zIndex
     * @param _isFixed
     * @param _srcRectX
     * @param _srcRectY
     */
    SpriteComponent(std::string _assetId = "", int _width = 0, int _height = 0, int _zIndex = 0, bool _isFixed = false,bool _flipH = false, int _srcRectX = 0, int _srcRectY = 0)
    {
        this->assetId = _assetId;
        this->width = _width;
        this->height = _height;
        this->zIndex = _zIndex;
        this->isFixed = _isFixed;
        this->srcRect = {_srcRectX, _srcRectY, _width, _height};
        this->flipH = _flipH;
    }
};

} // namespace
#endif // RETROGAMEENGINE_SPRITECOMPONENT_H
