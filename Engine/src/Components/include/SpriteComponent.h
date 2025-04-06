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
    bool flipH;
    SDL_Rect srcRect;
    int numberOfFrames;
    int speedRate;

    /**
     *
     * @param assetId
     * @param width
     * @param height
     * @param zIndex
     * @param isFixed
     * @param srcRectX
     * @param srcRectY
     * @param numberOfFrames
     * @param speedRate
     */
    SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int zIndex = 0, bool isFixed = false,bool flipH = false, int srcRectX = 0, int srcRectY = 0, int numberOfFrames = 0, int speedRate = 0)
    {
        this->assetId = assetId;
        this->width = width;
        this->height = height;
        this->zIndex = zIndex;
        this->isFixed = isFixed;
        this->flipH = flipH;
        this->srcRect = {srcRectX, srcRectY, width, height};
        this->numberOfFrames = numberOfFrames;
        this->speedRate = speedRate;
    }
};

} // namespace
#endif
