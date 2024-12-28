#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "../ECS/include/ECS.h"

#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"

#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
//#include "../Components/TransformComponent.h"

#include "../FSM/include/FSM.h"
#include "RGE.h"
#include <algorithm>

/**
 * @brief Detects key presses and changes the velocity.
 */
class PlayerControlComponent: public System
{
    public:
        PlayerControlComponent()
        {
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        // Subscribe to key pressed and key release event.
        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
        {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &PlayerControlComponent::OnKeyPressed);
            eventBus->SubscribeToEvent<KeyReleasedEvent>(this, &PlayerControlComponent::OnKeyReleased);
        }

        // Key pressed actions.
        void OnKeyPressed(KeyPressedEvent& event)
        {
            extern std::unique_ptr<Registry> g_registry;
            Entity player = g_registry->GetEntityByTag("player");

            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rb = player.GetComponent<RigidBodyComponent>();
            auto fsm = rb.fsm;

            switch (event.symbol)
            {
                case SDLK_UP:
                    fsm->toggle();
                    fsm->direction.y = -1.0;
                    fsm->isGrounded = false;

                    // Add acceleration force on the x axis.
                    rb.velocity.y -= (rb.speed + rb.acceleration);
                    if (rb.velocity.y < -(rb.speed + rb.maxAcceleration)) {
                        rb.velocity.y = -(rb.speed + rb.maxAcceleration);
                    }
                    break;
                case SDLK_RIGHT:
                    sprite.flipH = false;
                    fsm->toggle();
                    fsm->direction.x = 1.0;

                    // Add acceleration force on the x-axis.
                    rb.velocity.x += (rb.speed + rb.acceleration);
                    if (rb.velocity.x > (rb.speed + rb.maxAcceleration)) {
                        rb.velocity.x = (rb.speed + rb.maxAcceleration);
                    }
                    break;
                case SDLK_DOWN:
                    fsm->toggle();
                    fsm->direction.y = 1.0;

                    // Add acceleration force on the x axis.
                    rb.velocity.y += (rb.speed + rb.acceleration);
                    if (rb.velocity.y > (rb.speed + rb.maxAcceleration))
                    {
                        rb.velocity.y = (rb.speed + rb.maxAcceleration);
                    }
                    break;
                case SDLK_LEFT:
                    sprite.flipH = true;
                    fsm->toggle();
                    fsm->direction.x = -1.0;

                    // Add acceleration force on the x axis.
                    rb.velocity.x -= (rb.speed + rb.acceleration);
                    if (rb.velocity.x < -(rb.speed + rb.maxAcceleration)) {
                        rb.velocity.x = -(rb.speed + rb.maxAcceleration);
                    }
                    break;
                case SDLK_SPACE:
                    rb.velocity.y -= rb.jumpForce;
                    rb.fsm->isGrounded = false;
                    fsm->toggle();
                    fsm->direction.y = -1.0;
// Testing
//                    rb.velocity.y += sqrt(rb.jumpForce * -2.0f * rb.gravity);
                    break;
                default:
                    break;
            }
        }

        void OnKeyReleased(KeyReleasedEvent& event)
        {
            extern std::unique_ptr<Registry> g_registry;
            Entity player = g_registry->GetEntityByTag("player");

            auto& rb = player.GetComponent<RigidBodyComponent>();
            auto fsm = rb.fsm;

            switch (event.symbol)
            {
                case SDLK_UP:
                    fsm->toggle();
                    fsm->direction.y = 0.0;

                    rb.velocity.y -= (rb.speed + rb.acceleration);
                    if (rb.velocity.y <= 0.0f)
                    {
                        rb.velocity.y = 0.0f;
                    }
                    break;
                case SDLK_RIGHT:
                    fsm->toggle();
                    fsm->direction.x = 0.0;

                    rb.velocity.x -= (rb.speed + rb.acceleration);
                    if (rb.velocity.x >= 0.0f)
                    {
                        rb.velocity.x = 0.0f;
                    }
                    break;
                case SDLK_DOWN:
                    fsm->toggle();
                    fsm->direction.y = 0.0;

                    if (!rb.fsm->isGrounded)
                    {
                        rb.velocity.y -= (rb.speed + rb.acceleration);
                        if (rb.velocity.y >= 0.0f)
                        {
                            rb.velocity.y = 0.0f;
                        }
                    }
                    break;
                case SDLK_LEFT:
                    fsm->toggle();
                    fsm->direction.x = 0.0;

                    rb.velocity.x -= (rb.speed + rb.acceleration);
                    if (rb.velocity.x <= 0.0f)
                    {
                        rb.velocity.x = 0.0f;
                    }
                    break;
                case SDLK_SPACE:
                    // TODO NB. We do not need 2 direction vectors
//                    rb.direction.y = 1.0;
                    rb.velocity.y = 0.0;

                    rb.fsm->isGrounded = false;
                    fsm->toggle();
                    fsm->direction.y = 1.0;
                    break;
                default:
                    break;
            }
        }

};

#endif
