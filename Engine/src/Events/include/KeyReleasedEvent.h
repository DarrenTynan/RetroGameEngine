//
// Created by Darren Tynan on 05/02/2023.
//

#ifndef RETRO_ENGINE_KEYRELEASEDEVENT_H
#define RETRO_ENGINE_KEYRELEASEDEVENT_H

#include "../../ECS/include/ECS.h"
#include "../../EventBus/include/Event.h"
#include <SDL2/SDL.h>

using namespace RGE_EventBus;

namespace RGE_Events
{

class KeyReleasedEvent : public Event
{
public:
    SDL_Keycode symbol;
    explicit KeyReleasedEvent(SDL_Keycode symbol): symbol(symbol) {};
};

} // end namespace
#endif //RETRO_ENGINE_KEYRELEASEDEVENT_H
