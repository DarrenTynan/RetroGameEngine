#include <iostream>
#include "include/Editor.h"

int main()
{
    Editor::SetupSDL();
    Editor::Run();
    Editor::Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
