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
#include <algorithm>

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
                const auto playerComponent = entity.GetComponent<PlayerControllerComponent>();
                auto& spriteComponent = entity.GetComponent<SpriteComponent>();
                auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();
                auto& transformComponent = entity.GetComponent<TransformComponent>();
                auto& stateMachineComponent = entity.GetComponent<StateMachineComponent>();

                switch (event.symbol)
                {
                    case SDLK_UP:
                        rigidBodyComponent.velocity = playerComponent.upVelocity;
                        rigidBodyComponent.isGrounded = false;
                        stateMachineComponent.currentState = "up";
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.velocity = playerComponent.rightVelocity;
                        spriteComponent.flipH = false;
                        stateMachineComponent.currentState = "right";
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.velocity = playerComponent.downVelocity;
                        stateMachineComponent.currentState = "down";
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.velocity = playerComponent.leftVelocity;
                        spriteComponent.flipH = true;
                        stateMachineComponent.currentState = "left";
                        break;
                    case SDLK_SPACE:
                        rigidBodyComponent.velocity = playerComponent.upVelocity;
                        rigidBodyComponent.isGrounded = false;
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
//                auto& fsm = entity.GetComponent<StateMachineComponent>();

                switch (event.symbol)
                {
                    case SDLK_UP:
                        rigidBodyComponent.velocity = playerController.idleVelocity;
//                        fsm.currentState = "walk_up";
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        break;
                    default:
                        break;
                }
            }
        }

        void Update() { }

//    static void move(Entity *e)
//    {
//        e->dy += 1.5;
//
//        e->dy = MAX(MIN(e->dy, 18), -999);
//
//        e->isOnGround = 0;
//
//        moveToWorld(e, e->dx, 0);
//
//        moveToWorld(e, 0, e->dy);
//
//        e->x = MIN(MAX(e->x, 0), MAP_WIDTH * TILE_SIZE);
//        e->y = MIN(MAX(e->y, 0), MAP_HEIGHT * TILE_SIZE);
//    }
};

#endif
