//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_FSM_H
#define RETROGAMEENGINE_FSM_H

#include "BaseState.h"
#include <glm/glm.hpp>
#include "../ECS/include/ECS.h"

using namespace RGE_ECS;

namespace RGE_FSM
{

class BaseState;

/**
 * @brief Mandatory base functions.
 */
class FSM
{
public:
    bool isGrounded;

    glm::vec2 direction = glm::vec2(0.0, 0.0);

    FSM();
    [[nodiscard]] inline BaseState* getCurrentState() const { return currentState; }
    void toggle(Entity &entity);
    void setState(BaseState& newState, Entity &entity);

    void setIdleState(Entity &entity);
    void setWalkState(Entity &entity);
    void setJumpState(Entity &entity);
    void setFallState(Entity &entity);
private:
    BaseState* currentState;
};

} // end namespace
#endif //RETROGAMEENGINE_FSM_H
