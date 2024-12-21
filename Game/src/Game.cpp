//
// Created by Darren Tynan on 17/11/2024.
//

#include "../include/Game.h"
#include "../../RGE/include/RGE.h"

Game::Game() { Logger::Log("Game constructor called"); }
Game::~Game() { Logger::Log("Game deconstruct called"); }


/**
 * Function calls to setup: setupVars, setupSDL, setupRgeSDL, setupGameSDL, setupSystemRegistry, setupAssets.
 */
void Game::Setup()
{
    RGE::setupVars();
    RGE::setupSDL();
    RGE::setupRgeSDL();
    RGE::setupGameSDL();
    RGE::setupSystemRegistry();
    RGE::setupAssets();
    RGE::setupObjects();
    RGE::setupTMX();
    RGE::setupImGui();
}


/**
 * game main loop; processInputs, updateSystems and updateRender
 */
void Game::Run()
{
    bool isGameRunning = true;
    while (isGameRunning)
    {
        isGameRunning = RGE::processInputEvents();
        RGE::updateSystems();
        RGE::updateRenderer();
    }
}


/**
 * Destroy the RGE object.
 */
void Game::Destroy()
{
    RGE::destroy();
}

