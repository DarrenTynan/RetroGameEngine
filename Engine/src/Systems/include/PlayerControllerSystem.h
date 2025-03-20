#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include <algorithm>
#include <string>
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
 * @brief Detects key presses and changes the deltaXY.
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

        /**
         * @brief Subscribe to key pressed events.
         *
         * @param eventBus
         * @param _registry
         */
        void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus, std::shared_ptr<Registry>& _registry )
        {
            this->registry = _registry;

// EXAMPLE of subscribe to event.
//            eventBus->SubscribeToEvent<WalkLeftEvent>(this, &PlayerControllerSystem::WalkLeft);
//            void WalkLeft(WalkLeftEvent& event) {}

        }

        /**
         * @brief
         *
         * function _update()
         * player.dy+=gravity
         * player.dx*=friction
         *
         * --controls
         * if (btn(0)) then player.dx-=player.acc end -- left
         * if (btn(1)) then player.dx+=player.acc end -- right
         * if (btnp(5)) then player.dy-=player.boost end -- X
         *
         * --limit left/right speed
         * player.dx=mid(-player.max_dx,player.dx,player.max_dx)
         *
         * --limit fall speed
         * if (player.dy>0) then
         *  player.dy=mid(-player.max_dy,player.dy,player.max_dy)
         * end
         *
         * --apply dx and dy to player position
         * player.x+=player.dx
         * player.y+=player.dy
         *
         * --simple ground collision
         * if (player.y>110) then player.y=110 player.dy=0 end
         *
         * --if run off screen warp to other side
         * if (player.x>128) then player.x=-8 end
         * if (player.x<-8) then player.x=128 end
         * end
        */
        void Update(double deltaTime)
        {
            Entity player = registry->GetEntityByTag("player");
            auto &transform = player.GetComponent<TransformComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();

            // Apply forces to deltaXY
            rigidBody.deltaXY.x *= rigidBody.friction;
            rigidBody.deltaXY.y *= rigidBody.friction;

            ReadKeys();
        }


        /**
         * @brief Returns the middle value.
         *
         * @param a
         * @param b
         * @param c
         * @return the middle value
         */
        float MiddleOfThree(float a, float b, float c)
        {
            // Checking for b
            if ((a < b && b < c) || (c < b && b < a))
                return b;

            // Checking for a
            else if ((b < a && a < c) || (c < a && a < b))
                return a;

            else
                return c;
        }


        /**
         * @brief Player direction event. Flip the sprite, set the FSM and add acceleration.
         *
         * @param event
         */
        void WalkLeft()
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto &text = player.GetComponent<TextLabelComponent>().text;
            auto fsm = rigidBody.fsm;
            sprite.flipH = true;
            fsm->toggle();
            fsm->direction.x = -1.0;

            rigidBody.deltaXY.x -= rigidBody.acceleration;
            rigidBody.deltaXY.x = MiddleOfThree(-rigidBody.maxDeltaXY.x, rigidBody.deltaXY.x, rigidBody.maxDeltaXY.x);
            transform.position.x += rigidBody.deltaXY.x;
            text = "dx: " + std::to_string(rigidBody.deltaXY.x) + " dy: " + std::to_string(rigidBody.deltaXY.y)
                   + "\nmdx: " + std::to_string(rigidBody.maxDeltaXY.x) + " mdy: " + std::to_string(rigidBody.maxDeltaXY.y)
                   + "\ndir.x: " + std::to_string(fsm->direction.x) + " dir.y: " + std::to_string(fsm->direction.y);

        }


        /**
         * @brief Player direction event. Flip the sprite, set the FSM and add acceleration.
         *
         * @param event
         */
         void WalkRight()
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto &text = player.GetComponent<TextLabelComponent>().text;
            auto fsm = rigidBody.fsm;
            sprite.flipH = false;
            fsm->toggle();
            fsm->direction.x = 1.0;

            rigidBody.deltaXY.x += rigidBody.acceleration;
            rigidBody.deltaXY.x = MiddleOfThree(-rigidBody.maxDeltaXY.x, rigidBody.deltaXY.x, rigidBody.maxDeltaXY.x);
            transform.position.x += rigidBody.deltaXY.x;
            text = "dx: " + std::to_string(rigidBody.deltaXY.x) + " dy: " + std::to_string(rigidBody.deltaXY.y)
                   + "\nmdx: " + std::to_string(rigidBody.maxDeltaXY.x) + " mdy: " + std::to_string(rigidBody.maxDeltaXY.y)
                   + "\ndir.x: " + std::to_string(fsm->direction.x) + " dir.y: " + std::to_string(fsm->direction.y);

        }


        /**
         * @brief Player direction event. Flip the sprite, set the FSM and add acceleration.
         *
         * @param event
         */
         void WalkUp()
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto &text = player.GetComponent<TextLabelComponent>().text;
            auto fsm = rigidBody.fsm;
            fsm->toggle();
            fsm->direction.y = -1.0;

            rigidBody.deltaXY.y -= rigidBody.acceleration;
            rigidBody.deltaXY.y = MiddleOfThree(-rigidBody.maxDeltaXY.y, rigidBody.deltaXY.y, rigidBody.maxDeltaXY.y);
            transform.position.y += rigidBody.deltaXY.y;
            text = "dx: " + std::to_string(rigidBody.deltaXY.x) + " dy: " + std::to_string(rigidBody.deltaXY.y)
                   + "\nmdx: " + std::to_string(rigidBody.maxDeltaXY.x) + " mdy: " + std::to_string(rigidBody.maxDeltaXY.y)
                   + "\ndir.x: " + std::to_string(fsm->direction.x) + " dir.y: " + std::to_string(fsm->direction.y);
        }


        /**
         * @brief Player direction event. Flip the sprite, set the FSM and add acceleration.
         *
         * @param event
         */
         void WalkDown()
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto &text = player.GetComponent<TextLabelComponent>().text;
            auto fsm = rigidBody.fsm;
            fsm->toggle();
            fsm->direction.y = 1.0;

            rigidBody.deltaXY.y += rigidBody.acceleration;
            rigidBody.deltaXY.y = MiddleOfThree(-rigidBody.maxDeltaXY.y, rigidBody.deltaXY.y, rigidBody.maxDeltaXY.y);
            transform.position.y += rigidBody.deltaXY.y;
            text = "dx: " + std::to_string(rigidBody.deltaXY.x) + " dy: " + std::to_string(rigidBody.deltaXY.y)
                   + "\nmdx: " + std::to_string(rigidBody.maxDeltaXY.x) + " mdy: " + std::to_string(rigidBody.maxDeltaXY.y)
                   + "\ndir.x: " + std::to_string(fsm->direction.x) + " dir.y: " + std::to_string(fsm->direction.y);
        }


        void ReadKeys()
        {
            auto player = registry->GetEntityByTag("player");
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto fsm = rigidBody.fsm;
            fsm->direction.x = 0.0f;
            fsm->direction.y = 0.0f;
            auto &text = player.GetComponent<TextLabelComponent>().text;
            text = "dx: " + std::to_string(rigidBody.deltaXY.x) + " dy: " + std::to_string(rigidBody.deltaXY.y)
                   + "\nmdx: " + std::to_string(rigidBody.maxDeltaXY.x) + " mdy: " + std::to_string(rigidBody.maxDeltaXY.y)
                   + "\ndir.x: " + std::to_string(fsm->direction.x) + " dir.y: " + std::to_string(fsm->direction.y);


            SDL_PumpEvents();

            // update keyboard state
            auto keysArray = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));

            if (keysArray[SDL_SCANCODE_LEFT])
                WalkLeft();

            if (keysArray[SDL_SCANCODE_RIGHT])
                WalkRight();

            if (keysArray[SDL_SCANCODE_UP])
                WalkUp();

            if (keysArray[SDL_SCANCODE_DOWN])
                WalkDown();
        }
};

} // end namespace
#endif
