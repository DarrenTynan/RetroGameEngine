#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "../ECS/include/ECS.h"

#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"

#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

#include "../FSM/include/FSM.h"
#include "RGE.h"
#include <algorithm>

/**
 * @brief Player control system
 */
class PlayerControlSystem: public System
{
    public:
        PlayerControlSystem()
        {
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
            extern std::unique_ptr<Registry> g_registry;
            Entity player = g_registry->GetEntityByTag("player");

            auto& spriteComponent = player.GetComponent<SpriteComponent>();
            auto& rigidBodyComponent = player.GetComponent<RigidBodyComponent>();
            auto& transformComponent = player.GetComponent<TransformComponent>();
            auto fsm = rigidBodyComponent.fsm;

            const float PLAYER_MAX_SPEED = 1.0f;
            const float PLAYER_ACCELERATION = 0.2f;
            const float PLAYER_SPEED = 6.0f;
            switch (event.symbol)
            {
                case SDLK_UP:
//                    rigidBodyComponent.direction = playerControllerComponent.upVelocity;
                    fsm->toggle();
                    fsm->direction.y = -1.0;
                    fsm->isGrounded = false;
                    break;
                case SDLK_RIGHT:
//                    rigidBodyComponent.direction = playerControllerComponent.rightVelocity;
                    spriteComponent.flipH = false;
                    fsm->toggle();
                    fsm->direction.x = 1.0;

                    // The player is holding the "move forward" button
                    rigidBodyComponent.velocity.x += (PLAYER_SPEED + PLAYER_ACCELERATION);
                    if (rigidBodyComponent.velocity.x > (PLAYER_SPEED + PLAYER_MAX_SPEED)) {
                        rigidBodyComponent.velocity.x = (PLAYER_SPEED + PLAYER_MAX_SPEED);
                    }
                    break;
                case SDLK_DOWN:
//                    rigidBodyComponent.direction = playerControllerComponent.downVelocity;
                    fsm->toggle();
                    fsm->direction.y = 1.0;
                    break;
                case SDLK_LEFT:
//                    rigidBodyComponent.direction = playerControllerComponent.leftVelocity;
                    spriteComponent.flipH = true;
                    fsm->toggle();
                    fsm->direction.x = -1.0;

                    // The player is holding the "move forward" button
                    rigidBodyComponent.velocity.x -= (PLAYER_SPEED + PLAYER_ACCELERATION);
                    if (rigidBodyComponent.velocity.x < -(PLAYER_SPEED + PLAYER_MAX_SPEED)) {
                        rigidBodyComponent.velocity.x = -(PLAYER_SPEED + PLAYER_MAX_SPEED);
                    }
                    break;
                case SDLK_SPACE:
//                    rigidBodyComponent.velocity.y = playerControllerComponent.upVelocity.y - rigidBodyComponent.jumpForce;
                    rigidBodyComponent.fsm->isGrounded = false;
                    fsm->toggle();
                    fsm->direction.y = -1.0;
                    break;
                default:
                    break;
            }
        }

        void OnKeyReleased(KeyReleasedEvent& event)
        {

            extern std::unique_ptr<Registry> g_registry;
            Entity player = g_registry->GetEntityByTag("player");

            auto& sprite = player.GetComponent<SpriteComponent>();
            auto& rigidBodyComponent = player.GetComponent<RigidBodyComponent>();
            auto& transformComponent = player.GetComponent<TransformComponent>();
            auto fsm = rigidBodyComponent.fsm;

            const float PLAYER_ACCELERATION = 0.2f;
            const float PLAYER_SPEED = 80.0f;
            switch (event.symbol)
            {
                case SDLK_UP:
//                    rigidBodyComponent.direction = playerControllerComponent.idleVelocity;
                    fsm->toggle();
                    fsm->direction.y = 0.0;
                    break;
                case SDLK_RIGHT:
//                    rigidBodyComponent.direction = playerControllerComponent.idleVelocity;
                    fsm->toggle();
                    fsm->direction.x = 0.0;
                    rigidBodyComponent.velocity.x -= (PLAYER_SPEED + PLAYER_ACCELERATION);
                    if (rigidBodyComponent.velocity.x <= 0)
                    {
                        rigidBodyComponent.velocity.x = 0.0f;
                    }
                    break;
                case SDLK_DOWN:
//                    rigidBodyComponent.direction = playerControllerComponent.idleVelocity;
                    fsm->toggle();
                    fsm->direction.y = 0.0;
                    break;
                case SDLK_LEFT:
//                    rigidBodyComponent.direction = playerControllerComponent.idleVelocity;
                    fsm->toggle();
                    fsm->direction.x = 0.0;
                    rigidBodyComponent.velocity.x -= (PLAYER_SPEED + PLAYER_ACCELERATION);
                    if (rigidBodyComponent.velocity.x <= 0)
                    {
                        rigidBodyComponent.velocity.x = 0.0f;
                    }
                    break;
                case SDLK_SPACE:
//                    rigidBodyComponent.direction = playerControllerComponent.idleVelocity;
                    rigidBodyComponent.fsm->isGrounded = false;
                    fsm->toggle();
                    fsm->direction.y = 1.0;
                    break;
                default:
                    break;
            }
        }

        void Update() { }

};

#endif
