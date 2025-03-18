#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include <SDL2/SDL.h>
#include "RGE.h"
#include "../../Engine/src/FSM/include/FSM.h"

using namespace RGE_EventBus;

namespace RGE_Events
{

class KeyPressedEvent : public Event
{
public:
    SDL_Keycode symbol;

    explicit KeyPressedEvent(SDL_Keycode symbol): symbol(symbol)
    {}
};

} // end namespace

#endif
