//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/States.h"

/**
 * @brief Idle -> Walk transitions.
 *
 * @param entity
 */
void Idle::toggle(FSM* entity)
{
    entity->setState(Walk::getInstance());
}

BaseState& Idle::getInstance()
{
    static Idle singleton;
    return singleton;
}

void Idle::update(FSM *entity)
{
    std::cout << this->name << std::endl;
}

std::string Idle::getName() const
{
    return this->name;
}


/**
 * @brief Walk -> Idle transitions
 *
 * @param entity
 */
void Walk::toggle(FSM* entity)
{
    entity->setState(Idle::getInstance());
}

BaseState& Walk::getInstance()
{
    static Walk singleton;
    return singleton;
}

void Walk::update(FSM *entity)
{
    std::cout << this->name << std::endl;
}

std::string Walk::getName() const
{
    return this->name;
}


/**
 * @brief Run -> Walk transitions
 *
 * @param entity
 */
void Run::toggle(FSM *entity)
{
    entity->setState(Walk::getInstance());
}

BaseState& Run::getInstance()
{
    static Run singleton;
    return singleton;
}

void Run::update(FSM *entity)
{
    std::cout << this->name << std::endl;
}

std::string Run::getName() const
{
    return this->name;
}


/**
 * @brief Jump -> Fall transitions
 *
 * @param entity
 */
void Jump::toggle(FSM* entity)
{
    // Off -> Low
    entity->setState(Fall::getInstance());
}

BaseState& Jump::getInstance()
{
    static Jump singleton;
    return singleton;
}

void Jump::update(FSM *entity)
{
    std::cout << this->name << std::endl;
}

std::string Jump::getName() const
{
    return this->name;
}


/**
 * @brief Fall -> Idlde transitions
 *
 * @param entity
 */
void Fall::toggle(FSM* entity)
{
    entity->setState(Idle::getInstance());
}

BaseState& Fall::getInstance()
{
    static Fall singleton;
    return singleton;
}

void Fall::update(FSM *entity)
{
    std::cout << this->name << std::endl;
}

std::string Fall::getName() const
{
    return this->name;
}
