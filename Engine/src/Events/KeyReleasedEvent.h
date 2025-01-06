//
// Created by Darren Tynan on 05/02/2023.
//

#ifndef RETRO_ENGINE_KEYRELEASEDEVENT_H
#define RETRO_ENGINE_KEYRELEASEDEVENT_H

#include "../ECS/include/ECS.h"
#include "../EventBus/Event.h"
#include <SDL2/SDL.h>

class KeyReleasedEvent: public Event
{
public:
    SDL_Keycode symbol;
    explicit KeyReleasedEvent(SDL_Keycode symbol): symbol(symbol)
    {
//        if (symbol == SDLK_z)
//        {
//            std::cout << "KeyReleasedEvent z" << std::endl;
//        }
//        if (symbol == SDLK_x)
//        {
//            std::cout << "KeyReleasedEvent x" << std::endl;
//        }
    }
};

#endif //RETRO_ENGINE_KEYRELEASEDEVENT_H
