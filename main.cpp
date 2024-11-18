#include <iostream>
#include "Game/include/Game.h"
#include "RGE/src/RGE.cpp"

int main()
{
    // Initialise a new Game object
    Game game;

    RGE::sayHello();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
