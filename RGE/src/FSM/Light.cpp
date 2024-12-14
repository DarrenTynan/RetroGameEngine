//
// Created by Darren Tynan on 14/12/2024.
//

#include "include/Light.h"
#include "include/ConcreteLightState.h"

void Light::setState(LightState& newState)
{
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

void Light::toggle()
{
    currentState->toggle(this);
}

Light::Light()
{
    currentState = &LightOff::getInstance();
}
