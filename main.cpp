#include <iostream>
#include "Game/include/Game.h"
#include "Editor/include/Editor.h"

int main()
{
//    Game::Setup();
//    Game::Run();
//    Game::Destroy();

    Editor::Setup();
    Editor::Run();
    Editor::Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
