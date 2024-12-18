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
    std::string name = "Idle";
    void enter(FSM* entity) { std::cout << name << " enter" << std::endl; }
    void update(FSM* entity);
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << name << " exit" << std::endl; }
    static BaseState& getInstance();
    std::string getName() const;
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
    std::string name = "Walk";
    void enter(FSM* entity) { std::cout << name << " enter" << std::endl; }
    void update(FSM* entity);
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << name << " exit" << std::endl; }
    static BaseState& getInstance();
    std::string getName() const;
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
    void enter(FSM* entity) { std::cout << name << " enter" << std::endl; }
    void update(FSM* entity);
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << name << " exit" << std::endl; }
    static BaseState& getInstance();
    std::string getName() const;
private:
    Run() {};
    Run(const Run& other);
    Run& operator = (const Run& other);
};


class Jump : public BaseState
{
public:
    std::string name = "Jump";
    void enter(FSM* entity) { std::cout << name << " enter" << std::endl; }
    void update(FSM* entity);
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << name << " exit" << std::endl; }
    static BaseState& getInstance();
    std::string getName() const;
private:
    Jump() {};
    Jump(const Jump& other);
    Jump& operator = (const Jump& other);
};


class Fall : public BaseState
{
public:
    std::string name = "Fall";
    void enter(FSM* entity) { std::cout << name << " enter" << std::endl; }
    void update(FSM* entity);
    void toggle(FSM* entity);
    void exit(FSM* entity) { std::cout << name << " exit" << std::endl; }
    static BaseState& getInstance();
    std::string getName() const;
private:
    Fall() {};
    Fall(const Fall& other);
    Fall& operator = (const Fall& other);
};

#endif //RETROGAMEENGINE_ENTITYSTATE_H
