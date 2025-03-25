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
                    static_cast<int>(transform.position.x + collider.position.x - (float)camera.x),
                    static_cast<int>(transform.position.y + collider.position.y - (float)camera.y),
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
                                        (transform.position.x + collider.width/2.0f) - (float)camera.x,
                                        transform.position.y - (float)camera.y,
                                        (transform.position.x + collider.width/2.0f) - (float)camera.x,
                                        (transform.position.y - length - (float)camera.y)
                    );
                    // Down
                    SDL_RenderDrawLineF(renderer,
                                        (transform.position.x + collider.width/2) - (float)camera.x,
                                        (transform.position.y + collider.height) - (float)camera.y,
                                        (transform.position.x + collider.width/2) - (float)camera.x,
                                        (transform.position.y + collider.height + length) - (float)camera.y
                    );
                    // Left
                    SDL_RenderDrawLineF(renderer,
                                        transform.position.x - (float)camera.x,
                                        (transform.position.y + collider.height/2) - (float)camera.y,
                                        (transform.position.x - length) - (float)camera.x,
                                        (transform.position.y + collider.height/2) - (float)camera.y
                    );
                    // Right
                    SDL_RenderDrawLineF(renderer,
                                        transform.position.x + 32 - (float)camera.x,
                                        (transform.position.y + collider.height/2) - (float)camera.y,
                                        (transform.position.x + collider.width + length) - (float)camera.x,
                                        (transform.position.y + collider.height/2) - (float)camera.y
                    );

                }
            }

        }
};

} // end namespace
#endif
