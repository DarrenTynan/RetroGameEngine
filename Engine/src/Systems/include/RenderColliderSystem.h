#ifndef RENDERCOLLIDERSYSTEM_H
#define RENDERCOLLIDERSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../Components/include/TransformComponent.h"
#include "../../Components/include/BoxColliderComponent.h"
#include <SDL2/SDL.h>

using namespace RGE_Component;

namespace RGE_System
{

/**
 * @brief Iterate over all entities with a transform and box collider component
 * and draw a box for debug.
 */
class RenderColliderSystem: public System {
    public:
        RenderColliderSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<BoxColliderComponent>();
        }

        /**
         * @brief Draw the collision box's and ray-cast's.
         *
         * @param renderer
         * @param camera
         */
        void Update(SDL_Renderer* renderer, const SDL_Rect& camera)
        {
            for (auto entity: GetSystemEntities())
            {
                const auto transform = entity.GetComponent<TransformComponent>();
                const auto collider = entity.GetComponent<BoxColliderComponent>();

                SDL_Rect colliderRect ={
                    static_cast<int>(transform.position.x + collider.center.x - (float)camera.x),
                    static_cast<int>(transform.position.y + collider.center.y - (float)camera.y),
                    static_cast<int>(collider.width * transform.scale.x),
                    static_cast<int>(collider.height * transform.scale.y)
                };

                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(renderer, &colliderRect);

                if (collider.hasRaycast)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

                    // Up
                    SDL_RenderDrawLineF(renderer, collider.upCast.x, collider.upCast.y, collider.upCast.z, collider.upCast.w);
                    // Down
                    SDL_RenderDrawLineF(renderer, collider.downCast.x, collider.downCast.y, collider.downCast.z, collider.downCast.w);
                    // Left
                    SDL_RenderDrawLineF(renderer, collider.leftCast.x, collider.leftCast.y, collider.leftCast.z, collider.leftCast.w);
                    // Right
                    SDL_RenderDrawLineF(renderer, collider.rightCast.x, collider.rightCast.y, collider.rightCast.z, collider.rightCast.w);

                }
            }

        }
};

} // end namespace
#endif
