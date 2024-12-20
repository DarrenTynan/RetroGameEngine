//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/States.h"

/**
 * @brief Idle -> Walk transitions.
 *
 * @param fsm
 */
void Idle::toggle(FSM* fsm)
{
     fsm->setState(Walk::getInstance());
}

BaseState& Idle::getInstance()
{
    static Idle singleton;
    return singleton;
}

void Idle::update(FSM *fsm) {}

std::string Idle::getName()
{
    return "Idle";
}

void Idle::enter(FSM *fsm)
{
}

void Idle::exit(FSM *fsm)
{
}


/**
 * @brief Walk -> Idle transitions
 *
 * @param fsm
 */
void Walk::toggle(FSM* fsm)
{
    fsm->setState(Idle::getInstance());
}

BaseState& Walk::getInstance()
{
    static Walk singleton;
    return singleton;
}

void Walk::update(FSM *fsm) {}

std::string Walk::getName()
{
    return "Walk";
}

void Walk::enter(FSM *fsm)
{
}

void Walk::exit(FSM *fsm)
{
}


/**
 * @brief Run -> Walk transitions
 *
 * @param fsm
 */
void Run::toggle(FSM *fsm)
{
    fsm->setState(Walk::getInstance());
}

BaseState& Run::getInstance()
{
    static Run singleton;
    return singleton;
}

void Run::update(FSM *fsm) {}

std::string Run::getName()
{
    return "Run";
}

void Run::enter(FSM *fsm)
{
}

void Run::exit(FSM *fsm)
{
}


/**
 * @brief Jump -> Fall transitions
 *
 * @param fsm
 */
void Jump::toggle(FSM* fsm)
{
    fsm->setState(Fall::getInstance());
}

BaseState& Jump::getInstance()
{
    static Jump singleton;
    return singleton;
}

void Jump::update(FSM *fsm) {}

std::string Jump::getName()
{
    return "Jump";
}

void Jump::enter(FSM *fsm)
{
}

void Jump::exit(FSM *fsm)
{
}


/**
 * @brief Fall -> Idle transitions
 *
 * @param fsm
 */
void Fall::toggle(FSM* fsm)
{
    fsm->setState(Idle::getInstance());
}

BaseState& Fall::getInstance()
{
    static Fall singleton;
    return singleton;
}

void Fall::update(FSM *fsm) {}

std::string Fall::getName()
{
    return "Fall";
}

void Fall::enter(FSM *fsm)
{
}

void Fall::exit(FSM *fsm)
{
}

