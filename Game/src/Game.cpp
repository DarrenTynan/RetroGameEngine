//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"
#include "../../RGE/include/RGE.h"
#include <iostream>

Game::Game()
{
    Logger::Log("Game constructor called");
}

Game::~Game() { Logger::Log("Game deconstruct called"); }


/**
 * Setup the game data
 */
void Game::Setup()
{
    RGE::setupVars();
    RGE::setupSDL();
    RGE::setupRgeSDL();
    RGE::setupGameSDL();
    RGE::setupRegistry();
    RGE::setupAssets();
    RGE::setupTMX();
    RGE::setupObjects();
    RGE::setupImGui();

    // Set game running on
    isRunning = true;
}


/**
 * Main loop
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
 * Destroy
 */
void Game::Destroy()
{
    RGE::destroy();
}

