//
// Created by Darren Tynan on 30/03/2025.
//

#ifndef RETROGAMEENGINE_FSMCOMPONENT_H
#define RETROGAMEENGINE_FSMCOMPONENT_H

#include <sol/sol.hpp>
#include "../../Engine/src/FSM/include/FSM.h"

using namespace RGE_FSM;

namespace RGE_Component
{
    struct FSMComponent
    {
        // Pointer the lua state
//        sol::state &lua;
        // Pointer to the Finite State Machine
        FSM* fsm;

        explicit FSMComponent()
        {
            this->fsm = new FSM();
        }
    };

} // end namespace

#endif //RETROGAMEENGINE_FSMCOMPONENT_H




