//
// Created by Darren Tynan on 17/11/2024.
//

#ifndef RETROGAMEENGINE_RGE_H
#define RETROGAMEENGINE_RGE_H

#include <iostream>
#include <stdio.h>
#include <string>


/**
 * @brief definition pf the class functions.
 */
class RGE
{
public:
    static void InitialSetup();
    static void SetupGameSDL();
    static void UpdateRenderer();
    static bool ProcessDebugInputEvents();
    static void UpdateSystems();
    static void LoadLevel();
    static void SetupTMX();
    static void destroy();

private:

    static void DrawGrid();
};

#endif //RETROGAMEENGINE_RGE_H
