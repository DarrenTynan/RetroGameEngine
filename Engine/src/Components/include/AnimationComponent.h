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
    explicit AnimationComponent(int _numFrames = 1, int _fps = 1, bool _isLoop = true)
    {
        this->numFrames = _numFrames;
        this->currentFrame = 0;
        this->fps = _fps;
        this->isLoop = _isLoop;

    }

};


} // end namespace

#endif
