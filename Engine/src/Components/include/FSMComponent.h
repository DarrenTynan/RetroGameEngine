//
// Created by Darren Tynan on 30/03/2025.
//

#ifndef RETROGAMEENGINE_FSMCOMPONENT_H
#define RETROGAMEENGINE_FSMCOMPONENT_H

// #include <sol/sol.hpp>
#include "sol.hpp"
#include "../../Engine/src/FSM/include/FSM.h"

using namespace RGE_FSM;

namespace RGE_Component
{
    class FSMComponent
    {
    private:
        // Pointer to the Finite State Machine
        FSM* fsm;
    public:
        [[nodiscard]] FSM *getFsm() const
        {
            return fsm;
        }

        explicit FSMComponent()
        {
            this->fsm = new FSM();
        }
    };

} // end namespace

#endif //RETROGAMEENGINE_FSMCOMPONENT_H




