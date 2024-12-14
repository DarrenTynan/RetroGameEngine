//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_CONCRETELIGHTSTATE_H
#define RETROGAMEENGINE_CONCRETELIGHTSTATE_H

#include "LightState.h"
#include "Light.h"

class LightOff : public LightState
{
public:
    void enter(Light* light) {};
    void toggle(Light* light);
    void exit(Light* light) {};
    static LightState& getInstance();
private:
    LightOff() {};
    LightOff(const LightOff& other);
    LightOff& operator = (const LightOff& other);
};


/**
 * @brief Singleton as denoted by static getInstance() - Low intensity state
 */
class LowIntensity : public LightState
{
public:
    void enter(Light* light) {};
    void toggle(Light* light);
    void exit(Light* light) {};
    static LightState& getInstance();
private:
    LowIntensity() {}
    LowIntensity(const LowIntensity& other);
    LowIntensity& operator = (const LowIntensity& other);
};


/**
 * @brief Singleton as denoted by static getInstance() - Medium intensity state
 */
class MediumIntensity : public LightState
{
public:
    void enter(Light* light) {};
    void toggle(Light* light);
    void exit(Light* light) {};
    static LightState& getInstance();
private:
    MediumIntensity() {};
    MediumIntensity(const MediumIntensity& other);
    MediumIntensity& operator = (const MediumIntensity& other);
};


/**
 * @brief Singleton as denoted by static getInstance() - High intensity state
 */
class HighIntensity : public LightState
{
public:
    void enter(Light* light) {};
    void toggle(Light* light);
    void exit(Light* light) {};
    static LightState& getInstance();
private:
    HighIntensity() {};
    HighIntensity(const HighIntensity& other);
    HighIntensity& operator = (const HighIntensity& other);
};


#endif //RETROGAMEENGINE_CONCRETELIGHTSTATE_H
