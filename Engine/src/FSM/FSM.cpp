//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/FSM.h"
#include "include/States.h"

using namespace RGE_ECS;

namespace RGE_FSM
{

/**
 * @brief FSM constructor. Set the initial current state to Idle
 */
    FSM::FSM()
    {
        currentState = &Fall::getInstance();
        isGrounded = false;
        currentState->update(nullptr);
    }


/**
 * @brief Logic code for setState, Exit the current, set a new current and enter the new current.
 *
 * @param newState
 * @param entity
 */
    void FSM::setState(BaseState &newState, Entity &entity)
    {
        currentState->exit(this, entity);            // Do something before we chane state.
        currentState = &newState;                           // Change state.
        currentState->enter(this, entity);           // Do something after we change state.
    }


/**
 * @brief Delegate the task of determining the next state to the current state.
 * Calls the toggle method in the current state in StateTransitions.
 */
    void FSM::toggle(Entity &entity)
    {
        currentState->toggle(this,entity);
    }

/**
 * @brief Set states manually.
 */
    void FSM::setWalkState(Entity &entity)
    {
        setState(Walk::getInstance(),entity);
    }

    void FSM::setIdleState(Entity &entity)
    {
        setState(Idle::getInstance(),entity);
    }

    void FSM::setJumpState(Entity &entity)
    {
        setState(Jump::getInstance(),entity);
    }

    void FSM::setFallState(Entity &entity)
    {
        setState(Fall::getInstance(),entity);
    }

} // end namespace