//
// Created by Darren Tynan on 05/02/2023.
//

#ifndef RETRO_ENGINE_STATEMACHINESYSTEM_H
#define RETRO_ENGINE_STATEMACHINESYSTEM_H

#include "../ECS/include/ECS.h"
#include "../Components/SpriteComponent.h"
#include "../Components/StateMachineComponent.h"
#include "../Logger/Logger.h"

#include "../../RGE/src/FSM/include/FSM.h"


class StateMachineSystem: public System
{
public:
    static std::string debug;

    FSM* fsm{};
    StateMachineSystem()
    {
        fsm = new FSM();
        RequireComponent<SpriteComponent>();
        RequireComponent<StateMachineComponent>();
    }

    void ChangeState(const std::string& newState) {}

    void Update() const
    {
//        for (auto entity: GetSystemEntities()) {
//                auto& sprite = entity.GetComponent<SpriteComponent>();
//                sprite.flipH = true;
//            auto &state = entity.GetComponent<StateMachineComponent>();
//            Logger::Log("Current State: " + state.currentState);
//        }
    }

};
#endif //RETRO_ENGINE_STATEMACHINESYSTEM_H
