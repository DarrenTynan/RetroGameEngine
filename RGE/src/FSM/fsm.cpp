//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/FSM.h"
#include "include/States.h"
#include <string>

/**
 * @brief Logic code for setState, Exit the current, set a new current and enter the new current.
 *
 * @param newState
 */
void FSM::setState(BaseState& newState)
{
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

/**
 * @brief Toggle to a new state.
 */
void FSM::toggle()
{
    currentState->toggle(this);
}


/**
 * @brief FSM constructor. Set the initial current state to Idle
 */
FSM::FSM()
{
    std::cout << "FSM constructor" << std::endl;
    currentState = &Idle::getInstance();
}
