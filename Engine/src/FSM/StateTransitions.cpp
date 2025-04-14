//
// Created by Darren Tynan on 14/12/2024.
//

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
    return "idle_state";
}

void Idle::enter(FSM *fsm, Entity &entity)
{
    auto &animation = entity.GetComponent<AnimationComponent>();
    auto &sprite = entity.GetComponent<SpriteComponent>();
    auto frame = entity.GetComponent<SpritesheetComponent>().states.find("idle_state");

    sprite.srcRect = frame->second->srcRect;
    animation.currentFrame = 0;
    animation.numFrames = frame->second->numFrames;
    animation.fps = frame->second->fps;
}

void Idle::exit(FSM *fsm, Entity &entity) {}




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

std::string Walk::getName() { return "walk_state"; }

void Walk::enter(FSM *fsm, Entity &entity)
{
    auto &sprite = entity.GetComponent<SpriteComponent>();
    auto &animation = entity.GetComponent<AnimationComponent>();
    auto frame = entity.GetComponent<SpritesheetComponent>().states.find("walk_state");

    sprite.srcRect = frame->second->srcRect;
    animation.currentFrame = 0;
    animation.numFrames = frame->second->numFrames;
    animation.fps = frame->second->fps;
}

void Walk::exit(FSM *fsm, Entity &entity) {}




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

std::string Jump::getName() { return "jump_state"; }

void Jump::enter(FSM *fsm, Entity &entity)
{
    auto &sprite = entity.GetComponent<SpriteComponent>();
    auto frame =entity.GetComponent<SpritesheetComponent>().states.find("jump_state");
    auto &animation = entity.GetComponent<AnimationComponent>();

    sprite.srcRect = frame->second->srcRect;
    animation.currentFrame = 0;
    animation.numFrames = frame->second->numFrames;
    animation.fps = frame->second->fps;
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

std::string Fall::getName() { return "fall_state"; }

void Fall::enter(FSM *fsm, Entity &entity)
{
    auto &sprite = entity.GetComponent<SpriteComponent>();
    auto &animation = entity.GetComponent<AnimationComponent>();
    auto frame =entity.GetComponent<SpritesheetComponent>().states.find("fall_state");

    sprite.srcRect = frame->second->srcRect;
    animation.currentFrame = 0;
    animation.numFrames = frame->second->numFrames;
    animation.fps = frame->second->fps;
}

void Fall::exit(FSM *fsm, Entity &entity) {}

} // end namespace
