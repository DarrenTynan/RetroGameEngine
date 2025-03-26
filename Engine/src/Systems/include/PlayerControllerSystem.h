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
#include "../../Components/include/BoxColliderComponent.h"
#include "../../Components/include/TextLabelComponent.h"
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
 *
 * @param isGravity - set to true  if a platform game.
 */
class PlayerControllerSystem : public System
{
    public:
        std::shared_ptr<Registry> registry;

        bool isPlatformer = true;

        PlayerControllerSystem()
        {
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
            RequireComponent<BoxColliderComponent>();
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

            // Is it a platform game?
            if (isPlatformer)
                eventBus->SubscribeToEvent<JumpEvent>(this, &PlayerControllerSystem::Jump);

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
        void Update(double deltaTime, SDL_Rect& camera)
        {
            Entity player = registry->GetEntityByTag("player");
            auto &transform = player.GetComponent<TransformComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &collider = player.GetComponent<BoxColliderComponent>();
            auto fsm = rigidBody.fsm;

            // Apply forces to deltaXY
            rigidBody.deltaXY.x *= rigidBody.friction;

            if (isPlatformer && !fsm->isGrounded)
                rigidBody.deltaXY.y += rigidBody.gravity;
            else
                rigidBody.deltaXY.y *= rigidBody.friction;

            ReadKeys();

            // Update the ray's of the box collider.
            collider.upCast.x = (transform.position.x + collider.width/2.0f) - (float)camera.x;
            collider.upCast.y = transform.position.y - (float)camera.y;
            collider.upCast.z = (transform.position.x + collider.width/2.0f) - (float)camera.x;
            collider.upCast.w = (transform.position.y - collider.rayLength - (float)camera.y);

            collider.downCast.x = (transform.position.x + collider.width/2) - (float)camera.x;
            collider.downCast.y = (transform.position.y + collider.height) - (float)camera.y;
            collider.downCast.z = (transform.position.x + collider.width/2) - (float)camera.x;
            collider.downCast.w = (transform.position.y + collider.height + collider.rayLength) - (float)camera.y;

            collider.leftCast.x = transform.position.x - (float)camera.x;
            collider.leftCast.y = (transform.position.y + collider.height/2) - (float)camera.y;
            collider.leftCast.z = (transform.position.x - collider.rayLength) - (float)camera.x;
            collider.leftCast.w = (transform.position.y + collider.height/2) - (float)camera.y;

            collider.rightCast.x = transform.position.x + collider.width - (float)camera.x;
            collider.rightCast.y = (transform.position.y + collider.height/2) - (float)camera.y;
            collider.rightCast.z = (transform.position.x + collider.width + collider.rayLength) - (float)camera.x;
            collider.rightCast.w = (transform.position.y + collider.height/2) - (float)camera.y;

        }


        /**
         * @brief Read the keyboard for pump events NOT single click ie. jump, fire, etc.
         */
        void ReadKeys()
        {
            auto player = registry->GetEntityByTag("player");
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto fsm = rigidBody.fsm;

            SDL_PumpEvents();

            // update keyboard state
            auto keysArray = const_cast <Uint8*> (SDL_GetKeyboardState(nullptr));

            // Reset the key pressed switch.
            bool wasKeyPressed = false;

            if (keysArray[SDL_SCANCODE_LEFT])
            {
                WalkLeft();
                wasKeyPressed = true;
//                fsm->isGrounded = false;
            }

            if (keysArray[SDL_SCANCODE_RIGHT])
            {
                WalkRight();
                wasKeyPressed = true;
//                fsm->isGrounded = false;
            }

            if (!isPlatformer)
            {
                if (keysArray[SDL_SCANCODE_UP])
                {
                    WalkUp();
                    wasKeyPressed = true;
                }

            }

            // Is it a platform game?
            if (!isPlatformer)
            {
                if (keysArray[SDL_SCANCODE_DOWN])
                {
                    WalkDown();
                    wasKeyPressed = true;
                }

            }
            else if (isPlatformer && !fsm->isGrounded)
                Fall();

            // No keyboard selection, so we are at idle.
            if (!wasKeyPressed)
            {
                fsm->setIdleState();
                fsm->direction.x = 0;
                fsm->direction.y = 0;
            }
        }


        /**
         * @brief Helper function that returns the middle value to dampen down the Y axis.
         *
         * @param a
         * @param b
         * @param c
         * @return the middle value
         */
        static float MiddleOfThree(float a, float b, float c)
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
            auto fsm = rigidBody.fsm;
            sprite.flipH = true;
            fsm->direction.x = -1.0;

            if (fsm->getCurrentState()->getName() != "Walk")
                fsm->setWalkState();

            rigidBody.deltaXY.x -= rigidBody.acceleration;
            rigidBody.deltaXY.x = MiddleOfThree(-rigidBody.maxDeltaXY.x, rigidBody.deltaXY.x, rigidBody.maxDeltaXY.x);
            transform.position.x += rigidBody.deltaXY.x;

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
            auto fsm = rigidBody.fsm;
            sprite.flipH = false;
            fsm->direction.x = 1.0;

            if (fsm->getCurrentState()->getName() != "Walk")
                fsm->setWalkState();

            rigidBody.deltaXY.x += rigidBody.acceleration;
            rigidBody.deltaXY.x = MiddleOfThree(-rigidBody.maxDeltaXY.x, rigidBody.deltaXY.x, rigidBody.maxDeltaXY.x);
            transform.position.x += rigidBody.deltaXY.x;

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
            auto fsm = rigidBody.fsm;
            fsm->direction.y = -1.0;

            if (fsm->getCurrentState()->getName() != "Walk")
                fsm->setWalkState();

            fsm->isGrounded = false;

            std::cout << "PlayerControllerSystem DEBUG" << std::endl;

            rigidBody.deltaXY.y -= rigidBody.acceleration;
            rigidBody.deltaXY.y = MiddleOfThree(-rigidBody.maxDeltaXY.y, rigidBody.deltaXY.y, rigidBody.maxDeltaXY.y);
            transform.position.y += rigidBody.deltaXY.y;

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
            auto fsm = rigidBody.fsm;
            fsm->direction.y = 1.0;

            if (fsm->getCurrentState()->getName() != "Walk")
                fsm->setWalkState();

            rigidBody.deltaXY.y += rigidBody.acceleration;
            rigidBody.deltaXY.y = MiddleOfThree(-rigidBody.maxDeltaXY.y, rigidBody.deltaXY.y, rigidBody.maxDeltaXY.y);
            transform.position.y += rigidBody.deltaXY.y;

        }


        void Jump(JumpEvent& event)
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm = rigidBody.fsm;
            // Prevent double jump.
            if (!fsm->isGrounded)
                return;

            fsm->isGrounded = false;
            fsm->setJumpState();

            std::cout << "Jump Event" << std::endl;
            rigidBody.deltaXY.y -= rigidBody.boost;
            transform.position.y += rigidBody.deltaXY.y;
        }


        void Fall()
        {
            auto player = registry->GetEntityByTag("player");
            auto &sprite = player.GetComponent<SpriteComponent>();
            auto &rigidBody = player.GetComponent<RigidBodyComponent>();
            auto &transform = player.GetComponent<TransformComponent>();
            auto fsm = rigidBody.fsm;
            if (!fsm->isGrounded)
            {
                fsm->setFallState();
                fsm->direction.y = 1.0;

                std::cout << "Fall" << std::endl;
                transform.position.y += rigidBody.deltaXY.y;

            }
        }

};

} // end namespace
#endif
