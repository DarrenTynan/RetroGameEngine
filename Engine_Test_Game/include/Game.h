//
// Created by Darren Tynan on 17/11/2024.
//

#ifndef RETROGAMEENGINE_GAME_H
#define RETROGAMEENGINE_GAME_H

/**
 * @file Game.h
 * @brief Interface for the game class functions.
 */
class Game
{
public:
    Game();
    virtual ~Game();
    static void Setup();
    static void Run();
    static void Destroy();
};

#endif //RETROGAMEENGINE_GAME_H
