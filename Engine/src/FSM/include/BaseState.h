//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_BASESTATE_H
#define RETROGAMEENGINE_BASESTATE_H

#include "FSM.h"
#include <string>
#include "../ECS/include/ECS.h"

using namespace RGE_ECS;

namespace RGE_FSM
{

// Forward declaration to resolve circular dependency/include
class FSM;

/**
 * @brief Pure Virtual (interface) functions implicitly makes the class abstract.
 */
class BaseState
{
public:
    virtual void enter(FSM* fsm, Entity &entity) = 0;
    virtual void update(FSM* fsm) = 0;
    virtual void toggle(FSM* fsm, Entity &entity) = 0;
    virtual void exit(FSM* fsm, Entity &entity) = 0;
    virtual std::string getName() = 0;
    virtual ~BaseState() = default;
};

} // end namespace
#endif //RETROGAMEENGINE_BASESTATE_H
