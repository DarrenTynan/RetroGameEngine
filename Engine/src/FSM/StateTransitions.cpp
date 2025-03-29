//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/States.h"
#include "../Components/include/SpriteComponent.h"

using namespace RGE_Component;

namespace RGE_FSM
{

/**
 * @brief Idle -> Walk transitions.
 *
 * @param fsm
 */
void Idle::toggle(FSM* fsm, Entity &entity)
{
    fsm->setState(Walk::getInstance(),entity);
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

void Idle::enter(FSM *fsm, Entity &entity)
{
    entity.GetComponent<SpriteComponent>().assetId = "player-idle-image";
    std::cout << "StateTransitions: idle enter" << std::endl;
}

void Idle::exit(FSM *fsm)
{
    std::cout << "StateTransitions: idle exit" << std::endl;
}




/**
 * @brief Walk -> Idle transitions
 *
 * @param fsm
 */
void Walk::toggle(FSM* fsm, Entity &entity)
{
    fsm->setState(Idle::getInstance(),entity);
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

void Walk::enter(FSM *fsm, Entity &entity)
{
    entity.GetComponent<SpriteComponent>().assetId = "player-walk-image";
    std::cout << "StateTransitions: walk enter" << std::endl;
}

void Walk::exit(FSM *fsm)
{
    std::cout << "StateTransitions: walk exit" << std::endl;
}




/**
 * @brief Run -> Walk transitions
 *
 * @param fsm
 */
void Run::toggle(FSM *fsm, Entity &entity)
{
    fsm->setState(Walk::getInstance(), entity);
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

void Run::enter(FSM *fsm, Entity &entity) {}

void Run::exit(FSM *fsm) {}




/**
 * @brief Jump -> Fall transitions
 *
 * @param fsm
 */
void Jump::toggle(FSM* fsm, Entity &entity)
{
    fsm->setState(Fall::getInstance(),entity);
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

void Jump::enter(FSM *fsm, Entity &entity) {}

void Jump::exit(FSM *fsm) {}




/**
 * @brief Fall -> Idle transitions
 *
 * @param fsm
 */
void Fall::toggle(FSM* fsm, Entity &entity)
{
    fsm->setState(Idle::getInstance(),entity);
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

void Fall::enter(FSM *fsm, Entity &entity) {}

void Fall::exit(FSM *fsm) {}

} // end namespace
