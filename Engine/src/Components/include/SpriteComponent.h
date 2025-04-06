#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

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
     *
     * @param assetId
     * @param width
     * @param height
     * @param zIndex
     * @param isFixed
     * @param srcRectX
     * @param srcRectY
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
#endif
