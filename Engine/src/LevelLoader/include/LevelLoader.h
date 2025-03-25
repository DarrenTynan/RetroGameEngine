#ifndef LEVELLOADER_H
#define LEVELLOADER_H

/** @file */

#include <memory>
#include <SDL2/SDL.h>
#include "../../ECS/include/ECS.h"
#include "../../AssetStore/include/AssetStore.h"
#include "../libs/sol/sol.hpp"

using namespace RGE_AssetStore;
using namespace RGE_ECS;

namespace RGE_LevelLoader
{

/**
 * @brief Methods to load the level lua file and import sprite and tmx assets.
 */
class LevelLoader
{
public:
    static void LoadLevel(sol::state& lua,
                   const std::shared_ptr<Registry>& registry,
                   const std::unique_ptr<AssetStore>& assetStore,
                   SDL_Renderer* renderer,
                   int level
    );

    static void LoadTMX(const std::shared_ptr<Registry>& registry, const char * mapFile);
};

} // end namespace

#endif
