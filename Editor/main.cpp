#include <iostream>
#include "include/Editor.h"

int main()
{
//    EDITOR::Editor editor;
    Editor editor;

    editor.SetupSDL();
    editor.Run();
    editor.Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
