//
// Created by Darren Tynan on 16/03/2025.
//

#include "GlobalConfig.h"

namespace RGE_GlobalConfig
{
    int some_config_int = 123;
    std::string some_config_string = "foo";
}

bool RGE_GlobalConfig::load_config_file(sol::state& lua)
{
    // This checks the syntax of our script, but it does not execute the script
    sol::load_result script = lua.load_file("../Game_Engine/scripts/Config.lua");
    if (!script.valid())
    {
        sol::error error = script;
        std::string errorMessage = error.what();
        return false;
    }

    // Executes the script using the Sol state
    lua.script_file("../Game_Engine/scripts/Config.lua");

    // Read the big table for the current level
    sol::table config = lua["Config"];

    std::string window_title = config["title"];
    std::cout << window_title << std::endl;

    int window_width = config["window_width"];
    std::cout << window_width << std::endl;

    int window_height = config["window_height"];
    std::cout << window_height << std::endl;

    return true;
}
