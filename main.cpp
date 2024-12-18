#include <iostream>
#include "Game/include/Game.h"
#include "../../RGE/src/FSM/include/FSM.h"

int main()
{
//    FSM fsm;
//    fsm.toggle();
//    fsm.toggle();
//    fsm.toggle();
//    fsm.toggle();

    std::cout << "----------------------" << std::endl;

    // Game method calls
    Game::Setup();
    Game::Run();
    Game::Destroy();

//    RGE::sayHello();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
