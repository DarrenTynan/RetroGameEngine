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
class PlayerControllerSystem : public System
{
    public:
        std::shared_ptr<Registry> registry;

        PlayerControllerSystem()
        {
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        // Update position during Delta Time
        // player.dy += gravity
        // player.dx *= friction
        //
        // Key check:
        //  player.dx -=/+= acceleration
        //
        // Limit speed
        //
        // Apply DX:
        //  player.x += dx, player.y += dy
        //
        // Ground collision
        //
        // Check screen bounds
        void Update(double deltaTime)
        {
            Entity player = registry->GetEntityByTag("player");

            auto &transform = player.GetComponent<TransformComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();

            // Apply the velocityDelta
//            transform.position.x += (rigidBody.velocityDelta.x * (float)deltaTime);
//            transform.position.y += (rigidBody.velocityDelta.y * (float)deltaTime);

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

            eventBus->SubscribeToEvent<WalkLeftEvent>(this, &PlayerControllerSystem::WalkLeft);
            eventBus->SubscribeToEvent<WalkRightEvent>(this, &PlayerControllerSystem::WalkRight);
            eventBus->SubscribeToEvent<WalkUpEvent>(this, &PlayerControllerSystem::WalkUp);
            eventBus->SubscribeToEvent<WalkDownEvent>(this, &PlayerControllerSystem::WalkDown);
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
//            auto fsm = rigidBody.fsm;
//
//            sprite.flipH = true;
//            fsm->toggle();
//            fsm->direction.x = -1.0;

            // Add acceleration force on the x axis.
            rigidBody.velocityDelta.x -= rigidBody.acceleration;
            transform.position.x += rigidBody.velocityDelta.x;

            std::cout << "PlayerControllerSystem: Walk Left Event" << std::endl;
            std::cout << "velocityDelta.x: " << rigidBody.velocityDelta.x << std::endl;
            std::cout << "velocityDelta.y: " << rigidBody.velocityDelta.y << std::endl;
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
//            auto fsm = rigidBody.fsm;
//
//            sprite.flipH = false;
//            fsm->toggle();
//            fsm->direction.x = -1.0;

            // Add acceleration force on the x-axis.
            rigidBody.velocityDelta.x += rigidBody.acceleration;
            transform.position.x += rigidBody.velocityDelta.x;

            std::cout << "PlayerControllerSystem: Walk Right Event" << std::endl;
            std::cout << "velocityDelta.x: " << rigidBody.velocityDelta.x << std::endl;
            std::cout << "velocityDelta.y: " << rigidBody.velocityDelta.y << std::endl;
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
//            auto fsm = rigidBody.fsm;
//
//            fsm->toggle();
//            fsm->direction.y = -1.0;

            // Add acceleration force on the y-axis.
            rigidBody.velocityDelta.y -= rigidBody.acceleration;
            transform.position.y += rigidBody.velocityDelta.y;

            std::cout << "PlayerControllerSystem: Walk Up Event" << std::endl;
            std::cout << "velocityDelta.x: " << rigidBody.velocityDelta.x << std::endl;
            std::cout << "velocityDelta.y: " << rigidBody.velocityDelta.y << std::endl;
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
//            auto fsm = rigidBody.fsm;
//
//            fsm->toggle();
//            fsm->direction.y = 1.0;

            // Add acceleration force on the y-axis.
            rigidBody.velocityDelta.y += rigidBody.acceleration;
            transform.position.y -= rigidBody.velocityDelta.y;

            std::cout << "PlayerControllerSystem: Walk Down Event" << std::endl;
            std::cout << "velocityDelta.x: " << rigidBody.velocityDelta.x << std::endl;
            std::cout << "velocityDelta.y: " << rigidBody.velocityDelta.y << std::endl;
        }


};

} // end namespace
#endif
