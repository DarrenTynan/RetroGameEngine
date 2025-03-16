#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../EventBus/include/EventBus.h"

#include "../../Events/include/PlayerInputEvent.h"

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
 * @brief Detects key presses and changes the velocityDelta.
 */
class InputControlSystem : public System
{
    public:
        std::shared_ptr<Registry> registry;
        InputControlSystem()
        {
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        // Subscribe to key pressed and key release event.
        void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus, std::shared_ptr<Registry>& _registry )
        {
            this->registry = _registry;
            // Not needed atm.
//            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &InputControlSystem::OnKeyPressed);
//            eventBus->SubscribeToEvent<KeyReleasedEvent>(this, &InputControlSystem::OnKeyReleased);

            eventBus->SubscribeToEvent<WalkLeftEvent>(this, &InputControlSystem::WalkLeft);
            eventBus->SubscribeToEvent<WalkRightEvent>(this, &InputControlSystem::WalkRight);
            eventBus->SubscribeToEvent<WalkUpEvent>(this, &InputControlSystem::WalkUp);
            eventBus->SubscribeToEvent<WalkDownEvent>(this, &InputControlSystem::WalkDown);
            eventBus->SubscribeToEvent<JumpEvent>(this, &InputControlSystem::Jump);
        }

        // Player direction event
        void WalkLeft(WalkLeftEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm= rigidBody.fsm;
            sprite.flipH = true;
            fsm->toggle();
            fsm->direction.x = -1.0;

            // Add acceleration force on the x axis.
            rigidBody.velocityDelta.x -= rigidBody.acceleration;
            transform.position.x += rigidBody.velocityDelta.x;


            std::cout << "Walk Left Event" << std::endl;
        }


        // Player direction event
        void WalkRight(WalkRightEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm= rigidBody.fsm;
            sprite.flipH = false;
            fsm->toggle();
            fsm->direction.x = -1.0;

            // Add acceleration force on the x axis.
            rigidBody.velocityDelta.x += rigidBody.acceleration;
            transform.position.x += rigidBody.velocityDelta.x;


            std::cout << "Walk Right Event" << std::endl;
        }


        // Player direction event
        void WalkUp(WalkUpEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm= rigidBody.fsm;

            fsm->toggle();
            fsm->direction.y = -1.0;
            fsm->isGrounded = false;

            // Add acceleration force on the y axis.
            rigidBody.velocityDelta.y -= rigidBody.acceleration;

            std::cout << "Walk Up Event" << std::endl;
        }


        // Player direction event
        void WalkDown(WalkDownEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm= rigidBody.fsm;

            fsm->toggle();
            fsm->direction.y = 1.0;

            // Add acceleration force on the y axis.
            rigidBody.velocityDelta.y += rigidBody.acceleration;

            std::cout << "Walk Down Event" << std::endl;
        }


        // TODO shooting instead of jumping
        // Player direction event
        void Jump(JumpEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm= rigidBody.fsm;

            fsm->toggle();
            fsm->direction.y = -1.0;

            if (fsm->isGrounded)
            {
                rigidBody.velocityDelta.y -= rigidBody.jumpForce * 2;
                rigidBody.fsm->isGrounded = false;
            }

            // Add acceleration force on the y axis.
//            rigidBody.velocityDelta.y += rigidBody.acceleration;

            std::cout << "Walk Down Event" << std::endl;
        }


        // Key pressed actions.
        void OnKeyPressed(KeyPressedEvent& event)
        {
            std::cout << "Key pressed event: " << SDL_GetKeyName(event.symbol) << std::endl;
        }

        void OnKeyReleased(KeyReleasedEvent& event)
        {
            std::cout << "Key released event: " << SDL_GetKeyName(event.symbol) << std::endl;
        }

};

} // end namespace
#endif
