//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"
#include "../../Engine/src/Logger/Logger.h"
#include "RGE.h"

Game::Game() { Logger::Log("Game constructor called"); }
Game::~Game() { Logger::Log("Game deconstruct called"); }

/**
 * Function calls to setup: setupVars, setupSDL, SetupRgeSDL, SetupGameSDL, InitialSetup, LoadLevel.
 */
void Game::Setup()
{
    RGE::InitialSetup();
//    RGE::SetupRgeSDL();
    RGE::SetupGameSDL();
    RGE::LoadLevel();
    RGE::SetupTMX();
//    RGE::SetupImGui();
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

