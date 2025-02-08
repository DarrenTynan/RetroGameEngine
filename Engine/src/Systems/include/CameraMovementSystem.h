#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../../ECS/include/ECS.h"
#include "../../Components/include/CameraFollowComponent.h"
#include "../../Components/include/TransformComponent.h"
#include <SDL2/SDL.h>

using namespace RGE_System;

class CameraMovementSystem: public System {
    public:
        CameraMovementSystem()
        {
            RequireComponent<CameraFollowComponent>();
        }

        SDL_Rect view = {0,0,800 - 100,600 - 100 };


        void Update(SDL_Renderer* renderer, SDL_Rect& _camera)
        {
            // Center of window - 1/2 the width
            view.x = (_camera.w / 2) - (view.w / 2);
            view.y = (_camera.h / 2) - (view.h / 2);

            SDL_RenderDrawLineF(renderer, view.x, view.y, view.x + view.w, view.y );    // top
            SDL_RenderDrawLineF(renderer, view.x, view.y, view.x, view.h );    // left
            SDL_RenderDrawLineF(renderer, view.x, view.h, view.x + view.w, view.h );    // bottom
            SDL_RenderDrawLineF(renderer, view.x + view.w, view.y, view.x + view.w, view.h );    // right


//            for (auto entity: GetSystemEntities()) {
//                auto camera = entity.GetComponent<CameraFollowComponent>();

//                camera.position.x = transform.position.x;
//                camera.position.y = transform.position.y;
//                SDL_RenderDrawLineF(renderer, camera.position.x, camera.position.y, camera.position.x + camera.cameraWidth, camera.position.y );

//                if (transform.position.x + (camera.w / 2) < Game::mapWidth) {
//                    camera.x = transform.position.x - (Game::windowWidth / 2);
//                }
//
//                if (transform.position.y + (camera.h / 2) < Game::mapHeight) {
//                    camera.y = transform.position.y - (Game::windowHeight / 2);
//                }
//
//                // Keep camera rectangle view inside the screen limits
//                camera.x = camera.x < 0 ? 0 : camera.x;
//                camera.y = camera.y < 0 ? 0 : camera.y;
//                camera.x = (camera.x + camera.w > Game::mapWidth) ? Game::mapWidth - camera.w : camera.x;
//                camera.y = (camera.y + camera.h > Game::mapHeight) ? Game::mapHeight - camera.h : camera.y;
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderDrawRect(renderer, &_camera);
//            }
        }
};

#endif
