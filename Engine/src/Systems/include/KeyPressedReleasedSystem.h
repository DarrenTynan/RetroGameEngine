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
 * @brief Detects key presses and changes the velocityDelta.
 */
//    class B
//    {
//        A& a;
//        B( A& a_ )
//                : a( a_ )
//        {}
//    };
class KeyPressedReleasedSystem : public System
{
    public:
        KeyPressedReleasedSystem()
        {
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        // Subscribe to key pressed and key release event.
        void SubscribeToEvents( std::unique_ptr<EventBus>& eventBus, Entity _player )
        {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyPressedReleasedSystem::OnKeyPressed);
            eventBus->SubscribeToEvent<KeyReleasedEvent>(this, &KeyPressedReleasedSystem::OnKeyReleased);
        }

        // Key pressed actions.
        void OnKeyPressed(KeyPressedEvent& event)
        {
//            auto px = player.GetComponent<TransformComponent>().position.x;
//            std::cout << px << std::endl;

            std::cout << "Key pressed event: " << SDL_GetKeyName(event.symbol) << std::endl;
        }

        void OnKeyReleased(KeyReleasedEvent& event)
        {
            std::cout << "Key released event: " << SDL_GetKeyName(event.symbol) << std::endl;
        }

};

} // end namespace
#endif
