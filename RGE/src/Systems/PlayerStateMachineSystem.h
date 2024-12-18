//
// Created by Darren Tynan on 16/12/2024.
//

#ifndef RETROGAMEENGINE_PLAYERSTATEMACHINESYSTEM_H
#define RETROGAMEENGINE_PLAYERSTATEMACHINESYSTEM_H

#include "../ECS/include/ECS.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerStateMachineComponent.h"
#include "../Logger/Logger.h"
#include "../FSM/include/FSM.h"

class PlayerStateMachineSystem: public System
{
public:
    PlayerStateMachineSystem() {}

    void Update() {}

};

#endif //RETROGAMEENGINE_PLAYERSTATEMACHINESYSTEM_H
