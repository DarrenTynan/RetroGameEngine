//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"
#include "../../RGE/include/Engine.h"

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
    Engine::setupVars();
    Engine::setupSDL();
    Engine::setupRgeSDL();
    Engine::setupGameSDL();
    Engine::setupRegistry();
    Engine::setupAssets();
    Engine::setupObjects();
    Engine::setupTMX();
    Engine::setupImGui();

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
        isGameRunning = Engine::processInput();
        Engine::updateSystems();
        Engine::render();
    }
}


/**
 * Destroy
 */
void Game::Destroy()
{
    Engine::destroy();
}

