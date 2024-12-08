//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"
#include "../../RGE/include/RGE.h"

Game::Game() { Logger::Log("Game constructor called"); }

Game::~Game() { Logger::Log("Game deconstruct called"); }


/**
 * Function calls to setup: setupVars, setupSDL, setupRgeSDL, setupGameSDL, setupRegistry, setupAssets.
 */
void Game::Setup()
{
    RGE::setupVars();
    RGE::setupSDL();
    RGE::setupRgeSDL();
    RGE::setupGameSDL();
    RGE::setupRegistry();
    RGE::setupAssets();
    RGE::setupObjects();
    RGE::setupTMX();
    RGE::setupImGui();

    // Set game running on
//    isRunning = true;
}


/**
 * game main loop; processInputs, updateSystems and render
 */
void Game::Run()
{
    bool isGameRunning = true;
    while (isGameRunning)
    {
        isGameRunning = RGE::processInput();
        RGE::updateSystems();
        RGE::render();
    }
}


/**
 * Destroy the RGE object.
 */
void Game::Destroy()
{
    RGE::destroy();
}

