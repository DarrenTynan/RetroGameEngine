//
// Created by Darren Tynan on 16/12/2024.
//

#ifndef RETROGAMEENGINE_PLAYERSTATEMACHINECOMPONENT_H
#define RETROGAMEENGINE_PLAYERSTATEMACHINECOMPONENT_H

#include <iostream>

struct PlayerStateMachineComponent
{
    std::string currentState;

    explicit PlayerStateMachineComponent(std::string state = "default")
    {
        this->currentState = std::move(state);
    }

};


#endif //RETROGAMEENGINE_PLAYERSTATEMACHINECOMPONENT_H
