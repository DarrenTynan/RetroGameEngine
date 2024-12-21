//
// Created by Darren Tynan on 21/12/2024.
//

#ifndef RETROGAMEENGINE_GLOBALS_H
#define RETROGAMEENGINE_GLOBALS_H

// Debug keyboard toggles
bool g_isCollider = false;
bool g_isRayCast = false;

// Keep track off time for the render loop
int g_millisecsPreviouseFrame = 0;

SDL_Window* g_rgeWindow;
SDL_Rect g_rgeCamera;
SDL_Renderer* g_rgeRenderer;

SDL_Window* g_gameWindow;
SDL_Rect g_gameCamera;
SDL_Renderer* g_gameRenderer;

const auto g_MAP_PATH = "../Game/assets/tilemaps/TestLevel/TestLevel.tmx";
std::string g_mapImagePath;
tmx::Map g_map;

std::unique_ptr<Registry> g_registry;
std::unique_ptr<AssetStore> g_assetStore;
std::unique_ptr<EventBus> g_eventBus;

const int g_FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / g_FPS;
const ImVec4 g_game_clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
const ImVec4 g_rge_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
const int g_GAME_WINDOW_WIDTH = 800;
const int g_GAME_WINDOW_HEIGHT = 600;

#endif //RETROGAMEENGINE_GLOBALS_H
