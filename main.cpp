/**
 * @brief This just calls the hooks to the methods in Engine_Test_Game_Platform.
 * This is for the testing of the Engine and the hooks are set in concrete in order.
 */

#include <iostream>
#include "Engine_Test_Game_Platform/include/GameHook.h"

int main()
{
    GameHook::Setup();
    GameHook::Run();
    GameHook::Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
