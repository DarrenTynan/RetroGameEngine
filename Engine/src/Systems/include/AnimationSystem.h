#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../Components/include/SpriteComponent.h"
#include "../../Components/include/SpritesheetComponent.h"
#include "../../Components/include/AnimationComponent.h"
#include <SDL2/SDL.h>

using namespace RGE_System;

/**
 * @file AnimationSystem.h
 *
 * @brief Handle all the sprite animations.
 */
class AnimationSystem: public System
{
    public:

    AnimationSystem()
    {
        RequireComponent<SpriteComponent>();
        RequireComponent<AnimationComponent>();
    }

    /**
     * @brief Iterate over all entities and update the animation frame.
     */
    void Update()
    {
        for (auto entity: GetSystemEntities())
        {
            auto& animation = entity.GetComponent<AnimationComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();

            animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.fps / 1000) % animation.numFrames;
            if (entity.HasComponent<SpritesheetComponent>())
            {
                auto &fsmComponent = entity.GetComponent<FSMComponent>();
                auto fsm = fsmComponent.getFsm();
                auto frame = entity.GetComponent<SpritesheetComponent>().states.find(fsm->getCurrentState()->getName());
                sprite.srcRect = frame->second->srcRect;
                sprite.srcRect.x += animation.currentFrame * sprite.width;

            }
            else
                sprite.srcRect.x = animation.currentFrame * sprite.width;
        }
    }
};

#endif
