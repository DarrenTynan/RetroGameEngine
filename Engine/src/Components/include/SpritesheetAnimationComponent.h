#ifndef SPRITESHEETANIMATIONCOMPONENT_H
#define SPRITESHEETANIMATIONCOMPONENT_H

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
struct SpritesheetAnimationComponent
{
    int numFrames;
    int currentFrame;
    int fps;
    bool isLoop;
    u_int32_t startTime = SDL_GetTicks();

    /**
     * @brief Holds the variables needed for the animation system to loop over the frames.
     *
     * @param _numFrames
     * @param _fps
     * @param _isLoop
     */
    explicit SpritesheetAnimationComponent(int _numFrames = 1, int _fps = 1, bool _isLoop = true)
    {
        this->numFrames = _numFrames;
        this->currentFrame = 1;
        this->fps = _fps;
        this->isLoop = _isLoop;

    }

};


} // end namespace

#endif
