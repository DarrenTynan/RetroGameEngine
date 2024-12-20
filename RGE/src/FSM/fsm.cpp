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
void FSM::setState(BaseState& newState)
{
    currentState->exit(this);       // Do something before we chane state.
    currentState = &newState;             // Change state.
    currentState->enter(this);      // Do something after we change state.
}

/**
 * @brief Delegate the task of determining the next state to the current state.
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
    currentState = &Idle::getInstance();
    currentState->update(nullptr);
}
