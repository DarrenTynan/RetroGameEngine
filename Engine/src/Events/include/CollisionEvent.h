#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../../ECS/include/ECS.h"
#include "../../EventBus/include/Event.h"

namespace RGE_Events
{

class CollisionEvent: public Event
{
public:
    Entity a;
    Entity b;

    CollisionEvent(Entity a, Entity b): a(a), b(b)
    {
        // Player collision with BoxCollider
        auto& playerRigidBodyComponent = a.GetComponent<RigidBodyComponent>();

        // Check only for player object. Bounce back by 2 pixels away from object.
        if (playerRigidBodyComponent.velocityDelta.x != 0)
        {
            if (std::signbit(playerRigidBodyComponent.velocityDelta.x)) { a.GetComponent<TransformComponent>().position.x += 2.0f; }
            if (!std::signbit(playerRigidBodyComponent.velocityDelta.x)) { a.GetComponent<TransformComponent>().position.x -= 2.0f; }
            playerRigidBodyComponent.velocityDelta.x = 0.0f;
        }

        if (playerRigidBodyComponent.velocityDelta.y != 0)
        {
            if (std::signbit(playerRigidBodyComponent.velocityDelta.y)) { a.GetComponent<TransformComponent>().position.y += 2.0f; }
            if (!std::signbit(playerRigidBodyComponent.velocityDelta.y)) { a.GetComponent<TransformComponent>().position.y -= 2.0f; }
            playerRigidBodyComponent.velocityDelta.y = 0.0f;
        }

    }
};

} // end namespace
#endif
