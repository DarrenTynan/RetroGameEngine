#include <iostream>
#include "Game/include/Game.h"

int main()
{
    // Initialise a new Game object
//    Game game;

    // Game method calls
    Game::Setup();
    Game::Run();
    Game::Destroy();

//    Engine::sayHello();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
