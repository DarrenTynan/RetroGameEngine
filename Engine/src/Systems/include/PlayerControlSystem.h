#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include <algorithm>
#include "../../ECS/include/ECS.h"
#include "../../EventBus/include/EventBus.h"
#include "../../Events/include/PlayerInputEvent.h"
#include "../../Events/include/KeyPressedEvent.h"
#include "../../Events/include/KeyReleasedEvent.h"
#include "../../Components/include/RigidBodyComponent.h"
#include "../../Components/include/SpriteComponent.h"
#include "../../FSM/include/FSM.h"
#include "RGE.h"

using namespace RGE_EventBus;
using namespace RGE_Events;
using namespace RGE_ECS;
using namespace RGE_Component;

namespace RGE_System
{

/**
 * @brief Detects key presses and changes the velocityDelta.
 */
class PlayerControlSystem : public System
{
    public:
        std::shared_ptr<Registry> registry;

        PlayerControlSystem()
        {
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        /**
         * @brief Subscribe to key pressed events.
         *
         * @param eventBus
         * @param _registry
         */
        void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus, std::shared_ptr<Registry>& _registry )
        {
            this->registry = _registry;

            eventBus->SubscribeToEvent<WalkLeftEvent>(this, &PlayerControlSystem::WalkLeft);
            eventBus->SubscribeToEvent<WalkRightEvent>(this, &PlayerControlSystem::WalkRight);
            eventBus->SubscribeToEvent<WalkUpEvent>(this, &PlayerControlSystem::WalkUp);
            eventBus->SubscribeToEvent<WalkDownEvent>(this, &PlayerControlSystem::WalkDown);
        }


        /**
         * @brief Player direction event. Flip the sprite, set the FSM and add acceleration.
         *
         * @param event
         */
        void WalkLeft(WalkLeftEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm = rigidBody.fsm;

            sprite.flipH = true;
            fsm->toggle();
            fsm->direction.x = -1.0;

            // Add acceleration force on the x axis.
            rigidBody.velocityDelta.x -= rigidBody.acceleration;
            transform.position.x += rigidBody.velocityDelta.x;

//            std::cout << "PlayerControlSystem: Walk Left Event" << std::endl;
        }


        /**
         * @brief Player direction event. Flip the sprite, set the FSM and add acceleration.
         *
         * @param event
         */
        void WalkRight(WalkRightEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm = rigidBody.fsm;

            sprite.flipH = false;
            fsm->toggle();
            fsm->direction.x = -1.0;

            // Add acceleration force on the x-axis.
            rigidBody.velocityDelta.x += rigidBody.acceleration;
            transform.position.x += rigidBody.velocityDelta.x;

//            std::cout << "PlayerControlSystem: Walk Right Event" << std::endl;
        }


        /**
         * @brief Player direction event. Flip the sprite, set the FSM and add acceleration.
         *
         * @param event
         */
        void WalkUp(WalkUpEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm = rigidBody.fsm;

            fsm->toggle();
            fsm->direction.y = -1.0;
            fsm->isGrounded = false;

            // Add acceleration force on the y-axis.
            rigidBody.velocityDelta.y -= rigidBody.acceleration;

//            std::cout << "PlayerControlSystem: Walk Up Event" << std::endl;
        }


        /**
         * @brief Player direction event. Flip the sprite, set the FSM and add acceleration.
         *
         * @param event
         */
        void WalkDown(WalkDownEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm = rigidBody.fsm;

            fsm->toggle();
            fsm->direction.y = 1.0;

            // Add acceleration force on the y-axis.
            rigidBody.velocityDelta.y += rigidBody.acceleration;

//            std::cout << "PlayerControlSystem: Walk Down Event" << std::endl;
        }


};

} // end namespace
#endif
