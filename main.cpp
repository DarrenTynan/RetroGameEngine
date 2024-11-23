#include <iostream>
#include "Game/include/Game.h"
//#include "RGE/src/RGE.cpp"

#include "RGE/include/RGE.h"

int main()
{
    // Initialise a new Game object
    Game game;

    // Game method calls
    game.Initialize();
    game.Update();
    game.Destroy();


//    RGE::sayHello();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
