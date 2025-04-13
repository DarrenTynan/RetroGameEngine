#ifndef SPRITESHEETANIMATIONSYSTEM_H
#define SPRITESHEETANIMATIONSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../Components/include/SpritesheetComponent.h"
#include "../../Components/include/SpritesheetAnimationComponent.h"
#include <SDL2/SDL.h>

using namespace RGE_System;

/**
 * @file AnimationSystem.h
 *
 * @brief Handle all the sprite animations.
 */
class SpritesheetAnimationSystem: public System
{
    public:

    SpritesheetAnimationSystem()
    {
        RequireComponent<SpritesheetComponent>();
        RequireComponent<SpritesheetAnimationComponent>();
    }

    /**
     * @brief Iterate over all entities and update the animation frame.
     */
    void Update()
    {
        for (auto entity: GetSystemEntities())
        {
            auto& animation = entity.GetComponent<SpritesheetAnimationComponent>();
            auto& sprite = entity.GetComponent<SpritesheetComponent>();
            auto &fsmComponent = entity.GetComponent<FSMComponent>();
            auto fsm = fsmComponent.getFsm();
//            auto currentState = fsm->getCurrentState()->getName();
            animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.fps / 1000) % animation.numFrames;
//            sprite.srcRect.x = animation.currentFrame * sprite.width;
            auto frame = entity.GetComponent<SpritesheetComponent>().states.find(fsm->getCurrentState()->getName());
            frame->second->srcRect.x = animation.currentFrame * frame->second->width;
        }
    }
};

#endif
