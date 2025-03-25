//
// Created by Darren Tynan on 17/03/2025.
//

#include "include/LevelLoader.h"
#include "../Components/include/TransformComponent.h"
#include "../Components/include/RigidBodyComponent.h"
#include "../Components/include/SpriteComponent.h"
#include "../Components/include/AnimationComponent.h"
#include "../Components/include/BoxColliderComponent.h"
#include "../Components/include/CameraFollowComponent.h"
#include "../Components/include/ProjectileEmitterComponent.h"
#include "../Components/include/HealthComponent.h"
#include "../Components/include/TextLabelComponent.h"
#include "../Components/include/ScriptComponent.h"
#include "../Components/include/PlayerRaycastComponent.h"

#include <string>
#include <fstream>

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Object.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/Property.hpp>

//#include <sol/sol.hpp>
#include "../libs/sol/sol.hpp"

using namespace RGE_Component;

namespace RGE_LevelLoader
{

/**
 * @brief Load the Lua script describing level entities and tmx map
 *
 * @param lua           Pointer
 * @param registry      Pointer
 * @param assetStore    Pointer
 * @param renderer      Pointer
 * @param levelNumber   int
 */
void LevelLoader::LoadLevel(sol::state& lua, const std::shared_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, int levelNumber)
{
    std::string levelFilePath = "../Engine_Test_Game/scripts/Level";

    // This checks the syntax of our script, but it does not execute the script
    sol::load_result script = lua.load_file( levelFilePath + std::to_string(levelNumber) + ".lua");
    if (!script.valid())
    {
        sol::error error = script;
        std::string errorMessage = error.what();
//        Logger::Error("Error loading the lua script: " + errorMessage);
        exit(1);
    }

    // Executes the script using the Sol state
    lua.script_file(levelFilePath + std::to_string(levelNumber) + ".lua");

    // Read the big table for the current level
    sol::table level = lua["Level"];

    // Read the level assets
    sol::table assets = level["assets"];

    int i = 0;
    while (true)
    {
        sol::optional<sol::table> hasAsset = assets[i];
        if (hasAsset == sol::nullopt)
            break;

        sol::table asset = assets[i];
        std::string assetType = asset["type"];
        std::string assetId = asset["id"];

        if (assetType == "texture")
        {
            assetStore->AddTexture(renderer, assetId, asset["file"]);
//            Logger::Log("A new texture asset was added to the asset store, id: " + assetId);
        }

        if (assetType == "font")
        {
            assetStore->AddFont(assetId, asset["file"], asset["font_size"]);
//            Logger::Log("A new font asset was added to the asset store, id: " + assetId);
        }
        i++;
    }

    /**
     * @brief Read the level tilemap information
     */
    sol::table map = level["tilemap"];
    std::string mapFilePath = map["map_file"];

    LoadTMX(registry, mapFilePath.c_str());


    /**
     * @brief Read the level entities and their components
     */
    sol::table entities = level["entities"];

    i = 0;
    while (true)
    {
        sol::optional<sol::table> hasEntity = entities[i];
        if (hasEntity == sol::nullopt)
            break;

        sol::table entity = entities[i];

        Entity newEntity = registry->CreateEntity();

        // Tag
        sol::optional<std::string> tag = entity["tag"];
        if (tag != sol::nullopt)
            newEntity.AddTag(entity["tag"]);

        // Group
        sol::optional<std::string> group = entity["group"];
        if (group != sol::nullopt)
            newEntity.AddGroupTag(entity["group"]);

        // Components
        sol::optional<sol::table> hasComponents = entity["components"];
        if (hasComponents != sol::nullopt)
        {
            // Transform
            sol::optional<sol::table> transform = entity["components"]["transform"];

            if (transform != sol::nullopt)
            {
                newEntity.AddComponent<TransformComponent>(
                        glm::vec2(
                                entity["components"]["transform"]["start_position"]["x"],
                                entity["components"]["transform"]["start_position"]["y"]
                        ),
                        glm::vec2(
                                entity["components"]["transform"]["scale"]["x"].get_or(1.0),
                                entity["components"]["transform"]["scale"]["y"].get_or(1.0)
                        ),
                        entity["components"]["transform"]["rotation"].get_or(0.0)
                );
            }

            // RigidBody
            sol::optional<sol::table> rigidbody = entity["components"]["rigidbody"];
            if (rigidbody != sol::nullopt)
            {
                newEntity.AddComponent<RigidBodyComponent>(
                        glm::vec2(
                                entity["components"]["rigidbody"]["deltaXY"]["x"].get_or(0.0),
                                entity["components"]["rigidbody"]["deltaXY"]["y"].get_or(0.0)
                        ),
                        glm::vec2(
                                entity["components"]["rigidbody"]["maxDeltaXY"]["x"].get_or(3.0),
                                entity["components"]["rigidbody"]["maxDeltaXY"]["y"].get_or(3.0)
                        ),
                        float(
                                entity["components"]["rigidbody"]["acceleration"].get_or(0.5)
                        ),
                            float(
                                    entity["components"]["rigidbody"]["boost"].get_or(4.0)
                        ),
                            float(
                                    entity["components"]["rigidbody"]["gravity"].get_or(0.3)
                        ),
                            float(
                                    entity["components"]["rigidbody"]["friction"].get_or(0.85)
                        )
                );
            }

            // Sprite
            sol::optional<sol::table> sprite = entity["components"]["sprite"];
            if (sprite != sol::nullopt)
            {
                newEntity.AddComponent<SpriteComponent>(
                        entity["components"]["sprite"]["texture_asset_id"],
                        entity["components"]["sprite"]["width"],
                        entity["components"]["sprite"]["height"],
                        entity["components"]["sprite"]["z_index"].get_or(1),
                        entity["components"]["sprite"]["fixed"].get_or(false),
                        entity["components"]["sprite"]["src_rect_x"].get_or(0),
                        entity["components"]["sprite"]["src_rect_y"].get_or(0)
                );
            }

            // Animation
            sol::optional<sol::table> animation = entity["components"]["animation"];
            if (animation != sol::nullopt)
            {
                newEntity.AddComponent<AnimationComponent>(
                        entity["components"]["animation"]["num_frames"].get_or(1),
                        entity["components"]["animation"]["speed_rate"].get_or(1)
                );
            }

            // BoxCollider
            sol::optional<sol::table> collider = entity["components"]["box_collider"];
            if (collider != sol::nullopt)
            {
                newEntity.AddComponent<BoxColliderComponent>(
                        entity["components"]["box_collider"]["width"],
                        entity["components"]["box_collider"]["height"],
                        glm::vec2(
                                entity["components"]["box_collider"]["offset"]["x"].get_or(0),
                                entity["components"]["box_collider"]["offset"]["y"].get_or(0)
                        )
                );
            }

            sol::optional<sol::table> raycast = entity["components"]["ray_cast"];
            if (raycast != sol::nullopt)
            {
                newEntity.AddComponent<PlayerRaycastComponent>();
            }

            // Health
            sol::optional<sol::table> health = entity["components"]["health"];
            if (health != sol::nullopt)
            {
                newEntity.AddComponent<HealthComponent>(
                        static_cast<int>(entity["components"]["health"]["health_percentage"].get_or(100))
                );
            }

            // ProjectileEmitter
            sol::optional<sol::table> projectileEmitter = entity["components"]["projectile_emitter"];
            if (projectileEmitter != sol::nullopt)
            {
                newEntity.AddComponent<ProjectileEmitterComponent>(
                        glm::vec2(
                                entity["components"]["projectile_emitter"]["projectile_velocity"]["x"],
                                entity["components"]["projectile_emitter"]["projectile_velocity"]["y"]
                        ),
                        static_cast<int>(entity["components"]["projectile_emitter"]["repeat_frequency"].get_or(1)) *
                        1000,
                        static_cast<int>(entity["components"]["projectile_emitter"]["projectile_duration"].get_or(10)) *
                        1000,
                        static_cast<int>(entity["components"]["projectile_emitter"]["hit_percentage_damage"].get_or(
                                10)),
                        entity["components"]["projectile_emitter"]["friendly"].get_or(false)
                );
            }

            // CameraFollow
            sol::optional<sol::table> cameraFollow = entity["components"]["camera_follow"];
            if (cameraFollow != sol::nullopt)
            {
                newEntity.AddComponent<CameraFollowComponent>(static_cast<int>(map["tile_count_x"]),
                                                              static_cast<int>(map["tile_count_y"]),
                                                              static_cast<int>(map["tile_size"]),
                                                              static_cast<int>(entity["components"]["transform"]["start_position"]["x"]),
                                                              static_cast<int>(entity["components"]["transform"]["start_position"]["y"])
                );
            }

            // TextLabel
            sol::optional<sol::table> textLabel = entity["components"]["text_label"];
            if (textLabel != sol::nullopt)
            {
                newEntity.AddComponent<TextLabelComponent>();
            }

            // Script
            sol::optional<sol::table> _script = entity["components"]["on_update_script"];
            if (_script != sol::nullopt)
            {
                sol::function func = entity["components"]["on_update_script"][0];
                newEntity.AddComponent<ScriptComponent>(func);
            }
        }
        i++;
    }
}

/**
 * Load the tmx map files and iterate over.
 *
 * @return
 */
void LevelLoader::LoadTMX(const std::shared_ptr<Registry>& registry, const char * mapFile)
{
    tmx::Map map;
    const auto MAP_PATH = mapFile;
    std::string mapImagePath;

    unsigned int mapWidth;
    unsigned int mapHeight;
    unsigned int tileWidth;
    unsigned int tileHeight;
    unsigned int tileCountX;
    unsigned int tileCountY;

    if(map.load(MAP_PATH))
    {
        const auto& layers = map.getLayers();
        for(const auto& layer : layers)
        {
            // Get Object layer
            if(layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                for(const auto& object : objects)
                {
//                    std::cout << object.getName() << std::endl;

                    //do stuff with object properties
                    Entity tile = registry->CreateEntity();
                    tile.AddComponent<BoxColliderComponent>(object.getAABB().width, object.getAABB().height);
                    tile.AddComponent<TransformComponent>(glm::vec2(object.getAABB().left,  object.getAABB().top));
                    tile.AddTag(object.getName());
                }
            }
                // Get Tile layer
            else if(layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                //read out tile layer properties etc...

                const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();

                const auto& imagePath = map.getTilesets();
                mapImagePath = imagePath[0].getImagePath();

                // Tile width in pixels (32)
                tileWidth = map.getTileSize().x;
                // Tile height in pixels (32)
                tileHeight = map.getTileSize().x;
                // Image width
                unsigned int imageWidth = map.getTilesets().size();

                // How many tiles per row (25)
                tileCountX = map.getTileCount().x;
                mapWidth = map.getTileCount().x * tileWidth;
                // How many tiles per column (20)
                tileCountY = map.getTileCount().y;
                mapHeight = map.getTileCount().y * tileHeight;

                int index = 0;
                for (int y = 0; y < tileCountY; y++) {
                    for (int x = 0; x < tileCountX; x++) {
                        // Get the source rect pixel x,y position.
                        int tilesPerRow = imagePath[0].getImageSize().x / tileWidth;
                        int firstgid = 1;
                        int srcRectX = ( (tiles[index].ID - firstgid) % tilesPerRow )  * tileWidth;
                        int srcRectY = ( (tiles[index].ID - firstgid) / tilesPerRow ) * tileHeight;

                        Entity tile = registry->CreateEntity();
                        tile.AddTag("tile");

                        tile.AddComponent<TransformComponent>(glm::vec2(x * tileWidth, y * tileHeight), glm::vec2(1, 1), 0.0);
                        tile.AddComponent<SpriteComponent>("tilemap-image", tileWidth, tileHeight, 0, true, false, srcRectX, srcRectY);
                        index++;
                    }
                }
            }
        }
    }

}

} // end namespace
