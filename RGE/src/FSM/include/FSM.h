//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_FSM_H
#define RETROGAMEENGINE_FSM_H

//#include "GLOBALS.h"

#include "BaseState.h"

class BaseState;

/**
 * @brief Mandatory base functions.
 */
class FSM
{
public:
    FSM();
    [[nodiscard]] inline BaseState* getCurrentState() const { return currentState; }
    void toggle();
    void setState(BaseState& newState);
private:
    BaseState* currentState;
};

#endif //RETROGAMEENGINE_FSM_H
