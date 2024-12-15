//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_ENTITYSTATE_H
#define RETROGAMEENGINE_ENTITYSTATE_H

#include <iostream>
#include "fsmBaseState.h"
#include "FSM.h"


/**
 * @brief Singleton as denoted by static getInstance() - Low intensity state
 */
class Idle : public EntityState
{
public:
    void enter(FSM* entity) { std::cout << "Idle enter" << std::endl; };
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << "Idle exit" << std::endl; };
    static EntityState& getInstance();
private:
    Idle() {}
    Idle(const Idle& other);
    Idle& operator = (const Idle& other);
};


/**
 * @brief Singleton as denoted by static getInstance() - Medium intensity state
 */
class Walk : public EntityState
{
public:
    void enter(FSM* entity) { std::cout << "Walk enter" << std::endl; };
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << "Walk exit" << std::endl; };
    static EntityState& getInstance();
private:
    Walk() {};
    Walk(const Walk& other);
    Walk& operator = (const Walk& other);
};


/**
 * @brief Singleton as denoted by static getInstance() - High intensity state
 */
class Run : public EntityState
{
public:
    void enter(FSM* entity) { std::cout << "Run enter" << std::endl; };
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << "Run exit" << std::endl; };
    static EntityState& getInstance();
private:
    Run() {};
    Run(const Run& other);
    Run& operator = (const Run& other);
};


class Jump : public EntityState
{
public:
    void enter(FSM* entity) { std::cout << "Jump enter" << std::endl; };
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << "Jump exit" << std::endl; };
    static EntityState& getInstance();
private:
    Jump() {};
    Jump(const Jump& other);
    Jump& operator = (const Jump& other);
};


#endif //RETROGAMEENGINE_ENTITYSTATE_H
