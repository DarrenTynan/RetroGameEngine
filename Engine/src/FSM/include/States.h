//
// Created by Darren Tynan on 14/12/2024.
//

#ifndef RETROGAMEENGINE_ENTITYSTATE_H
#define RETROGAMEENGINE_ENTITYSTATE_H

#include <iostream>
#include "BaseState.h"

/**
 * @brief Singleton as denoted by static getInstance() - Low intensity state
 */
class Idle : public BaseState
{
public:
    std::string name = "Name: Idle";
    std::string getName();
    void enter(FSM* fsm);
    void update(FSM* fsm);
    void toggle(FSM* fsm);
    void toggleTest(FSM *fsm);
    void exit(FSM* fsm);
    static BaseState& getInstance();
private:
    Idle() {}
    Idle(const Idle& other);
    Idle& operator = (const Idle& other);
};


/**
 * @brief Singleton as denoted by static getInstance() - Medium intensity state
 */
class Walk : public BaseState
{
public:
    std::string name = "Name: Walk";
    std::string getName();
    void enter(FSM* fsm);
    void update(FSM* fsm);
    void toggle(FSM* fsm);
    void toggleTest(FSM *fsm);
    void exit(FSM* fsm);
    static BaseState& getInstance();
private:
    Walk() {};
    Walk(const Walk& other);
    Walk& operator = (const Walk& other);
};


/**
 * @brief Singleton as denoted by static getInstance() - High intensity state
 */
class Run : public BaseState
{
public:
    std::string name = "Run";
    std::string getName();
    void enter(FSM* fsm);
    void update(FSM* fsm);
    void toggle(FSM* fsm);
    void toggleTest(FSM *fsm);
    void exit(FSM* fsm);
    static BaseState& getInstance();
private:
    Run() {};
    Run(const Run& other);
    Run& operator = (const Run& other);
};


class Jump : public BaseState
{
public:
    std::string name = "Jump";
    std::string getName();
    void enter(FSM* fsm);
    void update(FSM* fsm);
    void toggle(FSM* fsm);
    void toggleTest(FSM *fsm);
    void exit(FSM* fsm);
    static BaseState& getInstance();
private:
    Jump() {};
    Jump(const Jump& other);
    Jump& operator = (const Jump& other);
};


class Fall : public BaseState
{
public:
    std::string name = "Fall";
    std::string getName();
    void enter(FSM* fsm);
    void update(FSM* fsm);
    void toggle(FSM* fsm);
    void toggleTest(FSM *fsm);
    void exit(FSM* fsm);
    static BaseState& getInstance();
private:
    Fall() {};
    Fall(const Fall& other);
    Fall& operator = (const Fall& other);
};

#endif //RETROGAMEENGINE_ENTITYSTATE_H
