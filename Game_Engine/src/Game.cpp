//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"
#include "RGE.h"

Game::Game() = default;
Game::~Game() = default;

/**
 * Function calls to setup: setupVars, setupSDL, SetupRgeSDL, SetupGameSDL, Setup, LoadLevel.
 */
void Game::Setup()
{
    RGE::Setup();
    RGE::LoadLevel();
}


/**
 * game main loop; processInputs, UpdateSystems and updateRender
 */
void Game::Run()
{
    bool isGameRunning = true;
    while (isGameRunning)
    {
        isGameRunning = RGE::ProcessDebugInputEvents();
        RGE::UpdateSystems();
        RGE::UpdateRenderer();
    }
}


/**
 * Destroy the Engine object.
 */
void Game::Destroy()
{
    RGE::destroy();
}

