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
            RequireComponent<TransformComponent>();
        }

        void Update(SDL_Renderer* renderer, SDL_Rect& _camera)
        {
            for (auto entity: GetSystemEntities())
            {
                auto transform = entity.GetComponent<TransformComponent>();
                auto cf = entity.GetComponent<CameraFollowComponent>();

                SDL_Rect viewBox = cf.frustum;
                SDL_RenderDrawRect(renderer, & viewBox);

                if (transform.position.x < (float)((cf.tileSize * cf.tileCountX) - cf.cameraOffsetX))
                    _camera.x = (int)transform.position.x - cf.cameraOffsetX;
                if (transform.position.x < (float)cf.cameraOffsetX)
                    _camera.x = 0;

                if (transform.position.y < (float)((cf.tileSize * cf.tileCountY) - cf.cameraOffsetY-32))
                    _camera.y = (int)transform.position.y - cf.cameraOffsetY;
                if (transform.position.y < (float)cf.cameraOffsetY)
                    _camera.y = 0;

                //Just move. Subtract the position of the player screen starting point
//                _camera.x = (int)transform.position.x - 32*10;
//                _camera.y = (int)transform.position.y - 32*5;

                // Keep camera rectangle view inside the screen limits
//                _camera.x = _camera.x < 0 ? 0 : _camera.x;
//                _camera.y = _camera.y < 0 ? 0 : _camera.y;
//                _camera.x = (_camera.x + _camera.w > cf.tileSize * cf.tileCountX) ? cf.tileSize * cf.tileCountX - _camera.w : _camera.x;
//                _camera.y = (_camera.y + _camera.h > cf.tileSize * cf.tileCountY) ? cf.tileSize * cf.tileCountY - _camera.h : _camera.y;

            }
        }
};

#endif
