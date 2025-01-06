#include <iostream>
#include "include/Editor.h"

int main()
{
    Editor::Setup();
    Editor::Run();
    Editor::Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
