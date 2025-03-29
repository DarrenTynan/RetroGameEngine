//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/FSM.h"
#include "include/States.h"

using namespace RGE_Component;

namespace RGE_FSM
{

/**
 * @brief FSM constructor. Set the initial current state to Idle
 */
    FSM::FSM()
    {
        currentState = &Idle::getInstance();
        isGrounded = false;
        currentState->update(nullptr);
    }


/**
 * @brief Logic code for setState, Exit the current, set a new current and enter the new current.
 *
 * @param newState
 */
    void FSM::setState(BaseState &newState)
    {
        currentState->exit(this);       // Do something before we chane state.
        currentState = &newState;            // Change state.
        currentState->enter(this);      // Do something after we change state.
    }


/**
 * @brief Delegate the task of determining the next state to the current state.
 * Calls the toggle method in the current state in StateTransitions.
 */
    void FSM::toggle()
    {
        currentState->toggle(this);
    }

/**
 * @brief Set states manually.
 */
    void FSM::setWalkState(SpriteComponent &sprite)
    {
        sprite.assetId = "player-walk-image";
        setState(Walk::getInstance());
    }

    void FSM::setIdleState(SpriteComponent &sprite)
    {
        sprite.assetId = "player-idle-image";
        setState(Idle::getInstance());
    }

    void FSM::setJumpState(SpriteComponent &sprite)
    {
        setState(Jump::getInstance());
    }

    void FSM::setFallState(SpriteComponent &sprite)
    {
        setState(Fall::getInstance());
    }

} // end namespace