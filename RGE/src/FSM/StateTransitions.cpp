//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/States.h"

/**
 * @brief Wak transitions
 *
 * @param entity
 */
void Idle::toggle(FSM* entity)
{
    // Low -> Medium
    entity->setState(Walk::getInstance());
}

BaseState& Idle::getInstance()
{
    static Idle singleton;
    return singleton;
}

void Idle::update(FSM *entity) {}

std::string Idle::getName() const
{
    return this->name;
}

/**
 * @brief Wak transitions
 *
 * @param entity
 */
void Walk::toggle(FSM* entity)
{
    // Medium -> High
    entity->setState(Run::getInstance());
}

BaseState& Walk::getInstance()
{
    static Walk singleton;
    return singleton;
}

void Walk::update(FSM *entity) {}

std::string Walk::getName() const
{
    return this->name;
}

/**
 * @brief Wak transitions
 *
 * @param entity
 */
void Run::toggle(FSM *entity)
{
    // High -> Low
    entity->setState(Jump::getInstance());
}

BaseState& Run::getInstance()
{
    static Run singleton;
    return singleton;
}

void Run::update(FSM *entity)
{

}

std::string Run::getName() const
{
    return this->name;
}

/**
 * @brief Wak transitions
 *
 * @param entity
 */
void Jump::toggle(FSM* entity)
{
    // Off -> Low
    entity->setState(Idle::getInstance());
}

BaseState& Jump::getInstance()
{
    static Jump singleton;
    return singleton;
}

void Jump::update(FSM *entity)
{

}

std::string Jump::getName() const
{
    return this->name;
}
