//
// Created by Darren Tynan on 27/12/2022.
//

#ifndef RETRO_ENGINE_MOVEMENTSYSTEM_H
#define RETRO_ENGINE_MOVEMENTSYSTEM_H

#include "../ECS/include/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem: public System
{
    public:
        MovementSystem()
        {
            RequireComponent<TransformComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void Update(double deltaTime)
        {
            for (auto entity: GetSystemEntities())
            {
                auto& transform = entity.GetComponent<TransformComponent>();
                auto rigidBody = entity.GetComponent<RigidBodyComponent>();

                transform.position.x += (rigidBody.velocity.x * deltaTime);
                transform.position.y += (rigidBody.velocity.y * deltaTime);

                if (transform.position.x < 0) transform.position.x = 0;
                if (transform.position.y < 0) transform.position.y = 0;

//                Logger::Log("Entity id = " + std::to_string(entity.GetId()) +
//                " position is now (" + std::to_string(transform.position.x) +
//                ", " + std::to_string(transform.position.y));
            }
        }
};

#endif //RETRO_ENGINE_MOVEMENTSYSTEM_H
