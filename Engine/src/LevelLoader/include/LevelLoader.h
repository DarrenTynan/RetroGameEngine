#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "../../ECS/include/ECS.h"
#include "../../AssetStore/include/AssetStore.h"
#include <SDL2/SDL.h>
#include <sol/sol.hpp>
#include <memory>

using namespace RGE_AssetStore;
using namespace RGE_ECS;

class LevelLoader
{
    public:
        static void LoadLevel(sol::state& lua,
                       const std::shared_ptr<Registry>& registry,
                       const std::unique_ptr<AssetStore>& assetStore,
                       SDL_Renderer* renderer,
                       int level
        );

        static void LoadConfig(sol::state& lua);
};

#endif
