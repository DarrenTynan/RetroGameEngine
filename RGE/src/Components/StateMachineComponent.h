//
// Created by Darren Tynan on 05/02/2023.
//

#ifndef RETRO_ENGINE_STATEMACHINECOMPONENT_H
#define RETRO_ENGINE_STATEMACHINECOMPONENT_H
#include <string>
#include <utility>

struct StateMachineComponent
{
    std::string currentState;

    explicit StateMachineComponent(std::string state = "idle") { this->currentState = std::move(state); }

};


#endif //RETRO_ENGINE_STATEMACHINECOMPONENT_H
