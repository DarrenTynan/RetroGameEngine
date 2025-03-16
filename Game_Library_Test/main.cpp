//
// Created by Darren Tynan on 16/02/2025.
//

#include <iostream>
#include "include/RGE.h"

int main()
{
    RGE::InitialSetup();
    RGE::SetupGameSDL();
    RGE::LoadLevel();
//    RGE::SetupTMX();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}

