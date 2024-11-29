//
// Created by Darren Tynan on 18/02/2023.
//

#ifndef RETRO_ENGINE_RENDERRAYCASTSYSTEM_H
#define RETRO_ENGINE_RENDERRAYCASTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RaycastComponent.h"
#include <SDL2/SDL.h>
#include <iostream>

class RenderRaycastSystem: public System {
    public:
        RenderRaycastSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RaycastComponent>();
        }

        void Update(SDL_Renderer* renderer, Entity player) {
            for (auto entity: GetSystemEntities()) {
                auto &trans = entity.GetComponent<TransformComponent>();
                auto& ray = entity.GetComponent<RaycastComponent>();
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                float length = 25.0f;
                // Up
                SDL_RenderDrawLineF(renderer, (trans.position.x + 64/2), trans.position.y, (trans.position.x + 64/2), (trans.position.y - length));
                // Down
                SDL_RenderDrawLineF(renderer, (trans.position.x + 64/2), (trans.position.y + 64), (trans.position.x + 64/2), (trans.position.y + 64 + length));
                // Left
                SDL_RenderDrawLineF(renderer, trans.position.x, (trans.position.y + 64/2), (trans.position.x - length), (trans.position.y + 64/2));
                // Right
                SDL_RenderDrawLineF(renderer, trans.position.x + 64, (trans.position.y + 64/2), (trans.position.x + 64 + length), (trans.position.y + 64/2));
            }
//            CalcRay(renderer);
                TestRay(renderer, player);
        }

        void TestRay(SDL_Renderer* renderer, Entity player) {
            RaycastComponent rc = player.GetComponent<RaycastComponent>();
            TransformComponent trans = player.GetComponent<TransformComponent>();

            // Get mouse position.
            int xPos;
            int yPos;
            SDL_GetMouseState(&xPos, &yPos);
            glm::vec2 mousePosition = glm::vec2((float)xPos, (float)yPos);

            // Store values in ray cast component
            rc.mousePosition = mousePosition;
            rc.rayStart = trans.position;
            rc.rayEnd = mousePosition;
            rc.mouseCell = mousePosition / rc.cellSize;
            rc.rayDirection = glm::normalize(rc.mousePosition - trans.position);
            rc.rayUnitStepSize = {sqrt(1 + (rc.rayDirection.y / rc.rayDirection.x) * (rc.rayDirection.y / rc.rayDirection.x)),
                                         sqrt(1 + rc.rayDirection.x / rc.rayDirection.y) * (rc.rayDirection.x / rc.rayDirection.y)
            };

            SDL_RenderDrawLineF(renderer, trans.position.x + 32, trans.position.y + 32, rc.mousePosition.x, rc.mousePosition.y);


        }

        void CalcRay(SDL_Renderer* renderer) {

            glm::vec2 player = glm::vec2(0, 0);
            glm::vec2 mapSize = glm::vec2(25.0,20.0);
            glm::vec2 cellSize = glm::vec2(32.0f, 32.0f);
            std::vector<int> vecMap;
            vecMap.resize((int)mapSize.x * (int)mapSize.y);

            glm::vec2 rayStart = player;
            glm::vec2 origin = glm::vec2(20.0f, 20.0f);
            glm::vec2 rayDirection = glm::normalize(origin - player);
            glm::vec2 rayUnitStepSize = {sqrt(1 + (rayDirection.y / rayDirection.x) * (rayDirection.y / rayDirection.x)),
                                      sqrt(1 + rayDirection.x / rayDirection.y) * (rayDirection.x / rayDirection.y)
            };
            glm::vec2 mapCheck = rayStart;
            glm::vec2 rayLength1D;
            glm::vec2 step;

            if (rayDirection.x < 0)
            {
                step.x = -1;
                rayLength1D.x = (rayStart.x - mapCheck.x) * rayUnitStepSize.x;
            }
            else
            {
                step.x = 1;
                rayLength1D.x = (mapCheck.x + 1) - rayStart.x * rayUnitStepSize.x;
            }
            if (rayDirection.y < 0)
            {
                step.y = -1;
                rayLength1D.y = (rayStart.y - mapCheck.y) * rayUnitStepSize.y;
            }
            else
            {
                step.y = 1;
                rayLength1D.y = (mapCheck.y + 1) - rayStart.y * rayUnitStepSize.y;
            }


            bool isTileFound = false;
            float maxDistance = 100.0f;
            float distance = 0.0f;

            while (!isTileFound && distance < maxDistance)
            {
                if (rayLength1D.x < rayLength1D.y)
                {
                    mapCheck.x += step.x;
                    distance = rayLength1D.x;
                    rayLength1D.x += rayUnitStepSize.x;
                }
                else
                {
                    mapCheck.y += step.y;
                    distance = rayLength1D.y;
                    rayLength1D.y = rayUnitStepSize.y;
                }

                if (mapCheck.x >= 0 && mapCheck.x < mapSize.x && mapCheck.y >= 0 && mapCheck.y < mapSize.y)
                {
                    // vecMap ??
                    if (mapSize[mapCheck.y * mapSize.x + mapCheck.x] == 1)
                    {
                        isTileFound = true;
                    }
                }
            }
            glm::vec2 intersection;
            if (isTileFound)
            {
                // Point of collision
                intersection = rayStart + rayDirection * distance;
                SDL_Rect colliderRect = {
                        static_cast<int>(intersection.x),
                        static_cast<int>(intersection.y),
                        32,
                        32
                };
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &colliderRect);
            }
        }

};

#endif //RETRO_ENGINE_RENDERRAYCASTSYSTEM_H
