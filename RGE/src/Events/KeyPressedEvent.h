#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include <SDL2/SDL.h>

class KeyPressedEvent: public Event
{
public:
    SDL_Keycode symbol;

    explicit KeyPressedEvent(SDL_Keycode symbol): symbol(symbol)
    {
//        if (symbol == SDLK_z)
//        {
//            std::cout << "KeyPressedEvent z" << std::endl;
//
//        }
//        if (symbol == SDLK_x)
//        {
//            std::cout << "KeyPressedEvent x" << std::endl;
//        }
    }
};

#endif
