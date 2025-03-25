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

        void Update(SDL_Renderer* renderer, const SDL_Rect& camera) {
            for (auto entity: GetSystemEntities()) {
                const auto transform = entity.GetComponent<TransformComponent>();
                const auto collider = entity.GetComponent<BoxColliderComponent>();

                SDL_Rect colliderRect = {
                    static_cast<int>(transform.position.x + collider.position.x - camera.x),
                    static_cast<int>(transform.position.y + collider.position.y - camera.y),
                    static_cast<int>(collider.width * transform.scale.x),
                    static_cast<int>(collider.height * transform.scale.y)
                };

                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(renderer, &colliderRect);

                if (collider.hasRaycast)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    float length = 25.0f;

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
            }

        }
};

} // end namespace
#endif
