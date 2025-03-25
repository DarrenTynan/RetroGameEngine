//
// Created by Darren Tynan on 25/03/2025.
//

#ifndef RETROGAMEENGINE_PLAYERRAYCASTCOMPONENT_H
#define RETROGAMEENGINE_PLAYERRAYCASTCOMPONENT_H

#include <glm/glm.hpp>

namespace RGE_Component
{

    struct PlayerRaycastComponent
    {
        glm::vec2 rayStart{};
        glm::vec2 rayEnd{};
        int rayLength;

        explicit PlayerRaycastComponent(glm::vec2 _rayStart = glm::vec2(0, 0), glm::vec2 _rayEnd = glm::vec2(0, 0), int _rayLength = 50)
        {
            this->rayStart = _rayStart;
            this->rayEnd = _rayEnd;
            this->rayLength = _rayLength;
        };

    };

} // end namespace

#endif //RETROGAMEENGINE_PLAYERRAYCASTCOMPONENT_H
