//
// Created by Darren Tynan on 16/02/2025.
//

#include <iostream>
#include "include/RGE.h"

int main()
{
    RGE::Setup();
    RGE::Destroy();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}

