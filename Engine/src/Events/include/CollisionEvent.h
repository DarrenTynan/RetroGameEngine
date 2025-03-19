//
// Created by Darren Tynan on 18/1/2024.
//

#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../../ECS/include/ECS.h"
#include "../../EventBus/include/Event.h"

namespace RGE_Events
{
    /**
     * @brief A collision occurred between two bounding boxes.
     */
    class CollisionEvent: public Event
    {
    public:
        Entity a;
        Entity b;

        CollisionEvent(Entity a, Entity b): a(a), b(b)
        {
            // Bypass if the entity is the player.
            if (a.HasTag("player") || b.HasTag("player"))
                std::cout << "CollisionEvent() with player" << std::endl;

        }
    };

} // end namespace

#endif //COLLISIONEVENT_H
