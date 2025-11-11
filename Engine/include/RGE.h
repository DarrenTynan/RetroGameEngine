//
// Created by Darren Tynan on 17/11/2024.
//

#ifndef RETROGAMEENGINE_RGE_H
#define RETROGAMEENGINE_RGE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <SDL_render.h>


/**
 * @brief definition pf the class functions.
 */
class RGE
{
public:
    static void Setup();
    static void SetupPlayer();
    static void UpdateRenderer();
    static bool ProcessKeyboardInputs();
    static void UpdateSystems();
    static void LoadLevel();
    static void Destroy();
    static void DebugWindowText();
    static bool HasWindowFocus(SDL_Window* window);
    static void ShowVersion();
};

#endif //RETROGAMEENGINE_RGE_H
