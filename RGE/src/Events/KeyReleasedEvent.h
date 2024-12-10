//
// Created by Darren Tynan on 05/02/2023.
//

#ifndef RETRO_ENGINE_KEYRELEASEDEVENT_H
#define RETRO_ENGINE_KEYRELEASEDEVENT_H

#include "../ECS/include/ECS.h"
#include "../EventBus/Event.h"
#include <SDL2/SDL.h>

class KeyReleasedEvent: public Event {
public:
    SDL_Keycode symbol;
    KeyReleasedEvent(SDL_Keycode symbol): symbol(symbol) {}
};

#endif //RETRO_ENGINE_KEYRELEASEDEVENT_H
