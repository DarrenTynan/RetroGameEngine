#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sol.hpp>

namespace RGE_Component
{

/**
 * @brief A small struct to hold the animation vars
 */
struct AnimationComponent
{
    int numFrames;
    int currentFrame;
    int frameSpeedRate;
    bool isLoop;
    u_int32_t startTime = SDL_GetTicks();

    explicit AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true)
    {
        this->numFrames = numFrames;
        this->currentFrame = 1;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;

    }

};


} // end namespace

#endif
