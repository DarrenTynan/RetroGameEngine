//
// Created by Darren Tynan on 18/02/2023.
//

#ifndef RETROGAMEENGINE_RENDERRAYCASTSYSTEM_H
#define RETROGAMEENGINE_RENDERRAYCASTSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../Components/include/TransformComponent.h"
#include "../../Components/include/BoxColliderComponent.h"
#include "../../Components/include/PlayerRaycastComponent.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace RGE_Component;
using namespace RGE_ECS;

namespace RGE_PlayerRaycast
{

class RenderPlayerRaycastSystem: public System
{
    public:
        RenderPlayerRaycastSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
            RequireComponent<PlayerRaycastComponent>();
        }

        void Update(SDL_Renderer* renderer, Entity player, const SDL_Rect& camera)
        {
            auto &transform = player.GetComponent<TransformComponent>();
            auto &collider = player.GetComponent<BoxColliderComponent>();
            auto $rayCast = player.GetComponent<PlayerRaycastComponent>();

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            float length = 25.0f;
//            SDL_Rect colliderRect = {
//                    static_cast<int>(transform.position.x + collider.offset.x - camera.x),
//                    static_cast<int>(transform.position.y + collider.offset.y - camera.y),
//                    static_cast<int>(collider.width * transform.scale.x),
//                    static_cast<int>(collider.height * transform.scale.y)
//            };
            // Up
            SDL_RenderDrawLineF(renderer,
                                (transform.position.x + 32.0f/2.0f) - camera.x,
                                transform.position.y - camera.y,
                                (transform.position.x + 32.0f/2.0f) - camera.x,
                                (transform.position.y - length - camera.y)
                                );
            // Down
            SDL_RenderDrawLineF(renderer,
                                (transform.position.x + 32/2) - camera.x,
                                (transform.position.y + 32) - camera.y,
                                (transform.position.x + 32/2) - camera.x,
                                (transform.position.y + 32 + length) - camera.y
                                );
            // Left
            SDL_RenderDrawLineF(renderer,
                                transform.position.x - camera.x,
                                (transform.position.y + 32/2) - camera.y,
                                (transform.position.x - length) - camera.x,
                                (transform.position.y + 32/2) - camera.y
                                );
            // Right
            SDL_RenderDrawLineF(renderer,
                                transform.position.x + 32 - camera.x,
                                (transform.position.y + 32/2) - camera.y,
                                (transform.position.x + 32 + length) - camera.x,
                                (transform.position.y + 32/2) - camera.y
                                );

    }

};

} // end namespace
#endif //RETROGAMEENGINE_RENDERRAYCASTSYSTEM_H
