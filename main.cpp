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
