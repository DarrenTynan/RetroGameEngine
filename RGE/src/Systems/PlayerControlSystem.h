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

#include "../FSM/include/FSM.h"
#include "RGE.h"
#include <algorithm>
//#include "Globals.h"

/**
 * @brief Player control system
 */
class PlayerControlSystem: public System
{
    public:
        PlayerControlSystem()
        {
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
                auto playerControllerComponent = entity.GetComponent<PlayerControllerComponent>();
                auto& spriteComponent = entity.GetComponent<SpriteComponent>();
                auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();
                auto& transformComponent = entity.GetComponent<TransformComponent>();
                auto fsm = rigidBodyComponent.fsm;

                switch (event.symbol)
                {
                    case SDLK_UP:
                        rigidBodyComponent.velocity = playerControllerComponent.upVelocity;
                        rigidBodyComponent.fsm->isGrounded = false;
                        fsm->toggle();
                        fsm->direction.y = -1.0;
                        fsm->isGrounded = false;
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.velocity = playerControllerComponent.rightVelocity;
                        spriteComponent.flipH = false;
                        fsm->toggle();
                        fsm->direction.x = 1.0;
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.velocity = playerControllerComponent.downVelocity;
                        fsm->toggle();
                        fsm->direction.y = 1.0;
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.velocity = playerControllerComponent.leftVelocity;
                        spriteComponent.flipH = true;
                        fsm->toggle();
                        fsm->direction.x = -1.0;
                        break;
                    case SDLK_SPACE:
                        rigidBodyComponent.velocity.y = playerControllerComponent.upVelocity.y - rigidBodyComponent.jumpForce;
                        rigidBodyComponent.fsm->isGrounded = false;
                        fsm->toggle();
                        fsm->direction.y = 1.0;
                        break;
                    default:
                        break;
                }
            }
        }

        void OnKeyReleased(KeyReleasedEvent& event)
        {
//            Entity player = g_registry->GetEntityByTag("player");

            for (auto entity: GetSystemEntities())
            {
                auto playerControllerComponent = entity.GetComponent<PlayerControllerComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();
                auto fsm = rigidBodyComponent.fsm;

                switch (event.symbol)
                {
                    case SDLK_UP:
                        rigidBodyComponent.velocity = playerControllerComponent.idleVelocity;
                        fsm->toggle();
                        fsm->direction.y = 0.0;
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.velocity = playerControllerComponent.idleVelocity;
                        fsm->toggle();
                        fsm->direction.x = 0.0;
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.velocity = playerControllerComponent.idleVelocity;
                        fsm->toggle();
                        fsm->direction.y = 0.0;
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.velocity = playerControllerComponent.idleVelocity;
                        fsm->toggle();
                        fsm->direction.x = 0.0;
                        break;
                    case SDLK_SPACE:
                        rigidBodyComponent.velocity.y = playerControllerComponent.upVelocity.y = rigidBodyComponent.gravityForce;
                        rigidBodyComponent.fsm->isGrounded = false;
                        fsm->toggle();
                        fsm->direction.y = -1.0;
                        break;
                    default:
                        break;
                }
            }
        }

        void Update() { }

};

#endif
