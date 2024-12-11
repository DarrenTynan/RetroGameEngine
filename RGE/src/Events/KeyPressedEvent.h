#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "../ECS/include/ECS.h"
#include "../EventBus/Event.h"
#include <SDL2/SDL.h>

class KeyPressedEvent: public Event
{
    public:
        SDL_Keycode symbol;
        explicit KeyPressedEvent(SDL_Keycode symbol): symbol(symbol) {}
};

#endif
