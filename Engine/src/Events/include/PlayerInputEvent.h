#ifndef PLAYERINPUTEVENT_H
#define PLAYERINPUTEVENT_H

#include <SDL2/SDL.h>
#include "RGE.h"
#include "../../Engine/src/FSM/include/FSM.h"

using namespace RGE_EventBus;

namespace RGE_Events
{

/**
 * @brief Handle walk left key input event
 */
class WalkLeftEvent : public Event
{
public:
    SDL_Keycode symbol;
    explicit WalkLeftEvent(SDL_Keycode symbol): symbol(symbol) {}
};


/**
 * @brief Handle walk right key input event
 */
class WalkRightEvent : public Event
{
public:
    SDL_Keycode symbol;
    explicit WalkRightEvent(SDL_Keycode symbol): symbol(symbol) {}
};


/**
 * @brief Handle walk up key input event
 */
class WalkUpEvent : public Event
{
public:
    SDL_Keycode symbol;
    explicit WalkUpEvent(SDL_Keycode symbol): symbol(symbol) {}
};


/**
 * @brief Handle walk down key input event
 */
class WalkDownEvent : public Event
{
public:
    SDL_Keycode symbol;
    explicit WalkDownEvent(SDL_Keycode symbol): symbol(symbol) {}
};


/**
 * @brief Handle jump key input event
 */
class JumpEvent : public Event
{
public:
    SDL_Keycode symbol;
    explicit JumpEvent(SDL_Keycode symbol): symbol(symbol) {}
};


/**
 * @brief Handle fire key input event
 */
class ProjectileEvent : public Event
{
public:
    SDL_Keycode symbol;
    explicit ProjectileEvent(SDL_Keycode symbol): symbol(symbol) {}
};


} // end namespace

#endif //PLAYERINPUTEVENT_H
