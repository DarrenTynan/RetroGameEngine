//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/FSM.h"
#include "include/States.h"

/**
 * @brief Logic code for setState, Exit the current, set a new current and enter the new current.
 *
 * @param newState
 */
void FSM::setState(EntityState& newState)
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
 * @brief FSM constructor.
 */
FSM::FSM()
{
    std::cout << "FSM constructor" << std::endl;
    currentState = &Idle::getInstance();
}

