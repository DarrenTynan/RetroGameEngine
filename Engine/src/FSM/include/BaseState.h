//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_BASESTATE_H
#define RETROGAMEENGINE_BASESTATE_H

#include "FSM.h"
//#include "../../Components/include/SpriteComponent.h"
#include <string>

//using namespace RGE_Component;

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
    virtual void enter(FSM* fsm) = 0;
    virtual void update(FSM* fsm) = 0;
    virtual void toggle(FSM* fsm) = 0;
    virtual void exit(FSM* fsm) = 0;
    virtual std::string getName() = 0;
    virtual ~BaseState() = default;
};

} // end namespace
#endif //RETROGAMEENGINE_BASESTATE_H
