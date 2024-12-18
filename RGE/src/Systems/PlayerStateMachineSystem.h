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
    FSM *fsm;
public:
    FSM *getFsm() const
    {
        return fsm;
    }

public:
    PlayerStateMachineSystem()
    {
        fsm = new FSM();
//        auto fsm = new FSM();
//        fsm->toggle();
//        fsm->toggle();
//        fsm->toggle();
//        fsm->toggle();

        RequireComponent<SpriteComponent>();
        RequireComponent<PlayerStateMachineComponent>();
    }

    void ChangeState(std::string newState)
    {
        fsm->toggle();
    }

    void Update()
    {
//        std::cout << "PlayerStateMachineSystem" << std::endl;
//        for (auto entity: GetSystemEntities())
//        {
//            auto &state = entity.GetComponent<PlayerStateMachineComponent>();
//            Logger::Log("Current State: " + state.currentState);
//        }
    }

};

#endif //RETROGAMEENGINE_PLAYERSTATEMACHINESYSTEM_H
