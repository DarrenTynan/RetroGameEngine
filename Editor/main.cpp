#include <iostream>
#include "include/Editor.h"

int main()
{
    EDITOR::Editor editor;
    editor.Setup();
    editor.Run();           // Not used as SetupImGui has a while loop to render
    editor.Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
