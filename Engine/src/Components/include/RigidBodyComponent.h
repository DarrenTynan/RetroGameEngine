#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>
#include "../../Engine/src/FSM/include/FSM.h"

//using namespace RGE_FSM;

namespace RGE_Component
{

/**
 * player.x is the number of pixels from the left that the player will start at.
 * player.y is the number of pixels from the top that the player will start at.
 * player.dx is the number of pixels that the player will move either left or right.
 * player.dy is the number of pixels that the player will move either up or down.
 * player.max_dx is the limit of how many pixels to allow the player to move left or right each frame.
 * player.max_dy is the limit of how many pixels to allow the player to move up or down each frame.
 * (We use the letter D before X and Y because in Mathematics we use the Greek letter "delta" to mean "change" or "how much something changes". So DX can be read as "how much X will change" or simply "change in X".)
 * player.acc (short for acceleration) is how much we add to DX when the player pushes the left or right buttons.
 * player.boost (jump power) is how much DY will suddenly decrease (making the player position higher) when the player pushes the jump button.
 * gravity (the force that constantly pulls "down") is how much DY will be increased every frame, all the time.
 * friction (the force that slows moving things down) is how much DX will be divided every frame, all the time.struct RigidBodyComponent
*/
struct RigidBodyComponent
{
    // Pointer to the Finite State Machine
    FSM* fsm = new FSM();

    // Entity velocity subject to forces is the rate of change. DX and DY
    glm::vec2 deltaXY = glm::vec2(0.0, .0);

    // Player maxDeltaXY is the limit of how many pixels to allow the player to move each frame.
    glm::vec2 maxDeltaXY = glm::vec2(3.0, 3.0);

    // Player forces
    float acceleration = 0.5f;
    float boost = 6.0f;
    float gravity = 0.3f;
    float friction = 0.85f;

    /**
     * @brief The option of passing in velocity for entities..
     *
     * @param _deltaXY
     * @param _maxDeltaXY
     * @param _acceleration
     * @param _boost
     * @param _gravity
     * @param _friction
    */
    explicit RigidBodyComponent(glm::vec2 _deltaXY = glm::vec2(), glm::vec2 _maxDeltaXY = glm::vec2(), float _acceleration = 0.5f, float _boost = 4.0f, float _gravity = 0.3f, float _friction = 0.85f)
    {
        this->deltaXY = _deltaXY;
        this->maxDeltaXY = _maxDeltaXY;
        this->acceleration = _acceleration;
        this->boost = _boost;
        this->gravity = _gravity;
        this->friction = _friction;
    }
};

} // end namespace
#endif //RIGIDBODYCOMPONENT_H
