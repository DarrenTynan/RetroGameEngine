#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../EventBus/include/EventBus.h"
#include "../../Events/include/KeyPressedEvent.h"
#include "../../Events/include/KeyReleasedEvent.h"
#include "../../Components/include/RigidBodyComponent.h"
#include "../../Components/include/SpriteComponent.h"
#include "../../FSM/include/FSM.h"
#include "RGE.h"
#include <algorithm>

using namespace RGE_EventBus;
using namespace RGE_Events;
using namespace RGE_ECS;
using namespace RGE_Component;

namespace RGE_System
{

/**
 * @brief Detects key presses and changes the velocity.
 */
class PlayerControllerSystem : public System
{
    public:
        PlayerControllerSystem()
        {
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        // Subscribe to key pressed and key release event.
        void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus )
        {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &PlayerControllerSystem::OnKeyPressed);
            eventBus->SubscribeToEvent<KeyReleasedEvent>(this, &PlayerControllerSystem::OnKeyReleased);
        }

        // Key pressed actions.
        void OnKeyPressed(KeyPressedEvent& event)
        {
            extern std::unique_ptr<Registry> registry;
            Entity player = registry->GetEntityByTag("player");

            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rb = player.GetComponent<RigidBodyComponent>();
            auto fsm= rb.fsm;

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
                    if (fsm->isGrounded)
                    {
                        rb.velocity.y += rb.jumpForce * 2;
                        rb.jumpCounter = rb.jumpFrames;
                        rb.fsm->isGrounded = false;
                    }
                    else if (rb.velocity.y > rb.jumpHeight)
                    {
                        rb.velocity.y = 0.0;
                        fsm->direction.y = 1.0;
                    }

                    fsm->toggle();
                    fsm->direction.y = -1.0;
                    break;
                default:
                    break;
            }
        }

        void OnKeyReleased(KeyReleasedEvent& event)
        {
            std::unique_ptr<Registry> registry;
            Entity player = registry->GetEntityByTag("player");

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
                    rb.jumpCounter = 0;
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

} // end namespace
#endif
