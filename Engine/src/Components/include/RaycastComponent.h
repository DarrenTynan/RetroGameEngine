//
// Created by Darren Tynan on 18/02/2023.
//

#ifndef RETRO_ENGINE_RAYCASTCOMPONENT_H
#define RETRO_ENGINE_RAYCASTCOMPONENT_H

#include <glm/glm.hpp>

namespace RGE_Component
{

struct RaycastComponent
{
    glm::vec2 rayStart;
    glm::vec2 rayEnd;
    glm::vec2 mapSize = glm::vec2(25, 20);
    glm::vec2 cellSize = glm::vec2(32, 32);
    glm::vec2 rayDirection;
    glm::vec2 mousePosition;
    glm::vec2 mouseCell;
    glm::vec2 rayUnitStepSize;

    RaycastComponent(glm::vec2 rayStart = glm::vec2(0))
    {
        this->rayStart = rayStart;
    };

};

} // end namespace
#endif //RETRO_ENGINE_RAYCASTCOMPONENT_H
