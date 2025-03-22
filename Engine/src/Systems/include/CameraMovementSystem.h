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
            int centerX = _camera.w / 2;
            int centerY = _camera.h / 2;
            int width = 400;
            int height = 200;
            int halfWidth = width / 2;
            int halfHeight = height / 2;

            SDL_Rect viewBox = {(centerX - halfWidth), (centerY - halfHeight), width, height };
            SDL_RenderDrawRect(renderer, & viewBox);

            // 32+10 and 32*5 are the starting x,y of the player. 32*6 is the extra offset of player height.
            for (auto entity: GetSystemEntities())
            {
                auto transform = entity.GetComponent<TransformComponent>();
                auto cf = entity.GetComponent<CameraFollowComponent>();

                if (transform.position.x < (cf.tileSize * cf.tileCountX) - 32*10)
                    _camera.x = (int)transform.position.x - 32*10;
                if (transform.position.x < 32*10)
                    _camera.x = 0;

                if (transform.position.y < (cf.tileSize * cf.tileCountY) - (32*6))
                    _camera.y = (int)transform.position.y - 32*5;
                if (transform.position.y < 32*5)
                    _camera.y = 0;

                //Just move. Subtract the offset of the player screen starting point
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
