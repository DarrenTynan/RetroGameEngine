#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../ECS/include/ECS.h"
#include "../EventBus/Event.h"

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
        if (playerRigidBodyComponent.velocity.x != 0)
        {
            if (std::signbit(playerRigidBodyComponent.velocity.x)) { a.GetComponent<TransformComponent>().position.x += 2.0f; }
            if (!std::signbit(playerRigidBodyComponent.velocity.x)) { a.GetComponent<TransformComponent>().position.x -= 2.0f; }
            playerRigidBodyComponent.velocity.x = 0.0f;
        }

        if (playerRigidBodyComponent.velocity.y != 0)
        {
            if (std::signbit(playerRigidBodyComponent.velocity.y)) { a.GetComponent<TransformComponent>().position.y += 2.0f; }
            if (!std::signbit(playerRigidBodyComponent.velocity.y)) { a.GetComponent<TransformComponent>().position.y -= 2.0f; }
            playerRigidBodyComponent.velocity.y = 0.0f;
        }

    }
};

#endif
