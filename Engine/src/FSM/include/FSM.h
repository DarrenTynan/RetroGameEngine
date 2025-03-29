//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_FSM_H
#define RETROGAMEENGINE_FSM_H

#include "BaseState.h"
#include <glm/glm.hpp>
#include "../Components/include/SpriteComponent.h"
using namespace RGE_Component;

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
    void toggle();
    void setState(BaseState& newState);

    void setIdleState(SpriteComponent &sprite);
    void setWalkState(SpriteComponent &sprite);
    void setJumpState(SpriteComponent &sprite);
    void setFallState(SpriteComponent &sprite);
private:
    BaseState* currentState;
};

} // end namespace
#endif //RETROGAMEENGINE_FSM_H
