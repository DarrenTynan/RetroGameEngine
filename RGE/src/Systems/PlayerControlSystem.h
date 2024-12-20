#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "../ECS/include/ECS.h"

#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"

#include "../Components/PlayerControllerComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/StateMachineComponent.h"

#include "../FSM/include/FSM.h"
#include "RGE.h"
#include <algorithm>

/**
 * @brief Player control system
 */
class PlayerControlSystem: public System
{
    public:

        FSM* fsm;

        PlayerControlSystem()
        {
            fsm = new FSM();
            RequireComponent<StateMachineComponent>();
            RequireComponent<PlayerControllerComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
            RequireComponent<TransformComponent>();
        }

        // Subscribe to key pressed and key release event.
        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
        {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &PlayerControlSystem::OnKeyPressed);
            eventBus->SubscribeToEvent<KeyReleasedEvent>(this, &PlayerControlSystem::OnKeyReleased);
        }

        // Key pressed actions.
        void OnKeyPressed(KeyPressedEvent& event)
        {

            for (auto entity: GetSystemEntities())
            {
                const auto playerControllerComponent = entity.GetComponent<PlayerControllerComponent>();
                auto& spriteComponent = entity.GetComponent<SpriteComponent>();
                auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();
                auto& transformComponent = entity.GetComponent<TransformComponent>();
                auto& stateMachineComponent = entity.GetComponent<StateMachineComponent>();

                switch (event.symbol)
                {
                    case SDLK_UP:
                        rigidBodyComponent.direction.y = -1.0;
                        rigidBodyComponent.velocity = playerControllerComponent.upVelocity;
                        rigidBodyComponent.isGrounded = false;
                        stateMachineComponent.currentState = "up";

                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.direction.x = 1.0;
                        rigidBodyComponent.velocity = playerControllerComponent.rightVelocity;
                        spriteComponent.flipH = false;
                        stateMachineComponent.currentState = "right";
                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.direction.y = 1.0;
                        rigidBodyComponent.velocity = playerControllerComponent.downVelocity;
                        stateMachineComponent.currentState = "down";
                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.direction.x = -1;
                        rigidBodyComponent.velocity = playerControllerComponent.leftVelocity;
                        spriteComponent.flipH = true;
                        stateMachineComponent.currentState = "left";
                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    case SDLK_SPACE:
                        rigidBodyComponent.velocity = playerControllerComponent.upVelocity;
                        rigidBodyComponent.isGrounded = false;
                        stateMachineComponent.currentState = "jump";
                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    default:
                        break;
                }
            }
        }

        void OnKeyReleased(KeyReleasedEvent& event)
        {
            for (auto entity: GetSystemEntities())
            {
                const auto playerController = entity.GetComponent<PlayerControllerComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();
                auto& finiteStateMachineComponent = entity.GetComponent<StateMachineComponent>();

                switch (event.symbol)
                {
                    case SDLK_UP:
                        rigidBodyComponent.direction.y = 0.0;
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        finiteStateMachineComponent.currentState = "idle";
                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.direction.x = 0.0;
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        finiteStateMachineComponent.currentState = "idle";
                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.direction.y = 0.0;
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        finiteStateMachineComponent.currentState = "idle";
                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.direction.x = 0.0;
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        finiteStateMachineComponent.currentState = "idle";
                        fsm->toggle();
                        std::cout << fsm->getCurrentState()->getName() << std::endl;
                        break;
                    default:
                        break;
                }
            }
        }

        void Update() { }

};

#endif
