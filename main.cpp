/**
 * @brief This just calls the hooks to the methods in Game_Engine.
 * This is for the testing of the Engine and the hooks are set in concrete in order.
 */

#include <iostream>
#include "Game_Engine/include/Game.h"

int main()
{
    Game::Setup();
    Game::Run();
    Game::Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
