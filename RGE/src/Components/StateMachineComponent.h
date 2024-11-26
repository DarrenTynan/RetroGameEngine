//
// Created by Darren Tynan on 05/02/2023.
//

#ifndef RETRO_ENGINE_STATEMACHINECOMPONENT_H
#define RETRO_ENGINE_STATEMACHINECOMPONENT_H
#include <string>

struct Entity {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int isOnGround;
    SDL_Texture *texture;
    long flags;
    Entity *next;
};
struct StateMachineComponent {
    std::string currentState;

    StateMachineComponent(std::string state = "idle") {
        this->currentState = state;
    }

};


#endif //RETRO_ENGINE_STATEMACHINECOMPONENT_H
