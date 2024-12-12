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


                // std::max
                // a: First value to be compared.
                // b: Second value to be compared.
                // comp: Binary function that accepts two values and returns a value convertible to bool.
                // It is optional and by default set to return true if the first element is larger than second.
                switch (event.symbol)
                {
                    case SDLK_UP:
//                        rigidBodyComponent.direction.y = -1;
//                        rigidBodyComponent.velocity = playerComponent.upVelocity;
                        rigidBodyComponent.direction.y = -1;
                        rigidBodyComponent.velocity = playerComponent.upVelocity * (rigidBodyComponent.delta.y += rigidBodyComponent.velocityMultiplier);
                        rigidBodyComponent.delta.y = std::max(std::min( rigidBodyComponent.delta.y, 10.0f ), -999.0f);

                        // Apply the velocity
//                        transform.position.x += (rigidBody.velocity.x * deltaTime);
//                        transform.position.y += (rigidBody.velocity.y * deltaTime);
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.direction.x = 1;
//                        rigidBodyComponent.velocity.x = (rigidBodyComponent.speed * rigidBodyComponent.direction.x);
                        rigidBodyComponent.velocity = playerComponent.rightVelocity * (rigidBodyComponent.delta.x += rigidBodyComponent.velocityMultiplier);
                        rigidBodyComponent.delta.x = std::max(std::min( rigidBodyComponent.delta.x, 10.0f ), -999.0f);
                        spriteComponent.flipH = false;
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.direction.y = 1;
                        rigidBodyComponent.velocity = playerComponent.downVelocity;
                        rigidBodyComponent.delta.y = std::max(std::min( rigidBodyComponent.delta.y, 10.0f ), -999.0f);
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.direction.x = -1;
                        rigidBodyComponent.velocity.x = (rigidBodyComponent.speed * rigidBodyComponent.direction.x);
                        rigidBodyComponent.delta.x = std::max(std::min( rigidBodyComponent.delta.y, 10.0f ), -999.0f);
                        spriteComponent.flipH = true;
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
                        rigidBodyComponent.direction = glm::vec2(0,0);
                        rigidBodyComponent.velocity = playerController.idleVelocity;
//                        fsm.currentState = "walk_up";
                        break;
                    case SDLK_RIGHT:
                        rigidBodyComponent.direction = glm::vec2(0,0);
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        break;
                    case SDLK_DOWN:
                        rigidBodyComponent.direction = glm::vec2(0,0);
                        rigidBodyComponent.velocity = playerController.idleVelocity;
                        break;
                    case SDLK_LEFT:
                        rigidBodyComponent.direction = glm::vec2(0,0);
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
