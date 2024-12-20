//
// Created by Darren Tynan on 05/02/2023.
//

#ifndef RETRO_ENGINE_STATEMACHINESYSTEM_H
#define RETRO_ENGINE_STATEMACHINESYSTEM_H

#include "../ECS/include/ECS.h"
#include "../Components/SpriteComponent.h"
#include "../Logger/Logger.h"

class StateMachineSystem: public System
{
public:
    static std::string debug;

    StateMachineSystem()
    {
        RequireComponent<SpriteComponent>();
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
