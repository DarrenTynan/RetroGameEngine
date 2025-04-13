//
// Created by Darren Tynan on 14/12/2024.
//

#include <rapidjson/document.h>
#include "include/States.h"
#include "../Components/include/AnimationComponent.h"
#include "../Components/include/SpriteComponent.h"
#include "../Components/include/SpritesheetComponent.h"
#include "include/FSM.h"

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
    // TODO we need to get the animation setting from the lue table.

    // Change animation
//    entity.GetComponent<SpriteComponent>().assetId = "player-idle-image";
//    entity.GetComponent<SpriteComponent>().srcRect.x = 0;
    auto frame =entity.GetComponent<SpritesheetComponent>().states.find("idle_state");
    entity.GetComponent<SpriteComponent>().srcRect = frame->second->srcRect;
}

void Idle::exit(FSM *fsm, Entity &entity)
{
    // TODO we need to get the animation setting from the lue table.
    // Restore current animation

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
//    entity.GetComponent<SpriteComponent>().assetId = "player-walk-image";
//    entity.GetComponent<SpriteComponent>().srcRect.x = 32*6;
//    std::cout << "StateTransitions: walk enter" << std::endl;
    auto frame =entity.GetComponent<SpritesheetComponent>().states.find("walk_state");
    entity.GetComponent<SpriteComponent>().srcRect = frame->second->srcRect;
}

void Walk::exit(FSM *fsm, Entity &entity)
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

void Run::exit(FSM *fsm, Entity &entity) {}




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

void Jump::enter(FSM *fsm, Entity &entity)
{
    auto frame =entity.GetComponent<SpritesheetComponent>().states.find("jump_state");
    entity.GetComponent<SpriteComponent>().srcRect = frame->second->srcRect;
}

void Jump::exit(FSM *fsm, Entity &entity) {}




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

void Fall::enter(FSM *fsm, Entity &entity)
{
    auto frame =entity.GetComponent<SpritesheetComponent>().states.find("fall_state");
    entity.GetComponent<SpriteComponent>().srcRect = frame->second->srcRect;
}

void Fall::exit(FSM *fsm, Entity &entity) {}

} // end namespace
