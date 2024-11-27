#include <iostream>
#include "Game/include/Game.h"

int main()
{
    // Initialise a new Game object
    Game game;

    // Game method calls
    game.Setup();
    game.Run();
    game.Destroy();


//    RGE::sayHello();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
