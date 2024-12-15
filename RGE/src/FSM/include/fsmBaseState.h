//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_ENTITYBASESTATE_H
#define RETROGAMEENGINE_ENTITYBASESTATE_H

#include "FSM.h"

// Forward declaration to resolve circular dependency/include
class FSM;

/**
 * @brief Pure Virtual (interface) functions implicitly makes the class abstract.
 */
class EntityState
{
public:
    virtual void enter(FSM* light) = 0;
    virtual void toggle(FSM* light) = 0;
    virtual void exit(FSM* light) = 0;
    virtual ~EntityState() = default;
};


#endif //RETROGAMEENGINE_ENTITYBASESTATE_H
