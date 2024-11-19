#include <iostream>
#include "Game/include/Game.h"
#include "RGE/src/RGE.cpp"

int main()
{
    // Initialise a new Game object
    Game game;

    // Game method calls
    game.Initialize();
//    game.Run();
    game.Destroy();


//    RGE::sayHello();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
