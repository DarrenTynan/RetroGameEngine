#include <iostream>
#include "Game/include/Game.h"
#include "Editor/include/Editor.h"

int main()
{
    Game::Setup();
    Game::Run();
    Game::Destroy();

//    EDITOR::Editor editor;
//
//    editor.SetupSDL();
//    editor.SetupImGui();
//    editor.Run();
//    editor.Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
