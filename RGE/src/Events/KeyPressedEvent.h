#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include <SDL2/SDL.h>
#include "RGE.h"
#include "../../RGE/src/FSM/include/FSM.h"

class KeyPressedEvent: public Event
{
public:
    SDL_Keycode symbol;

    explicit KeyPressedEvent(SDL_Keycode symbol): symbol(symbol)
    {}
};

#endif
