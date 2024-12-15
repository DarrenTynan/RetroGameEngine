//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/States.h"

/**
 * @brief Transitions for the base functions layed out in EntityBaseSate.h
 *
 * @param entity
 */
void Idle::toggle(FSM* entity)
{
    // Low -> Medium
    entity->setState(Walk::getInstance());
}

EntityState& Idle::getInstance()
{
    static Idle singleton;
    return singleton;
}


void Walk::toggle(FSM* entity)
{
    // Medium -> High
    entity->setState(Run::getInstance());
}

EntityState& Walk::getInstance()
{
    static Walk singleton;
    return singleton;
}


void Run::toggle(FSM *entity)
{
    // High -> Low
    entity->setState(Jump::getInstance());
}

EntityState& Run::getInstance()
{
    static Run singleton;
    return singleton;
}


void Jump::toggle(FSM* entity)
{
    // Off -> Low
    entity->setState(Idle::getInstance());
}

EntityState& Jump::getInstance()
{
    static Jump singleton;
    return singleton;
}

