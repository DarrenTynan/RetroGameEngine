//
// Created by Darren Tynan on 16/03/2025.
//

#ifndef RETROGAMEENGINE_GLOBALCONFIG_H
#define RETROGAMEENGINE_GLOBALCONFIG_H

#include <string>
#include "../libs/sol/sol.hpp"

namespace RGE_GlobalConfig
{
    extern int some_config_int;

    extern std::string window_title;
    extern int window_width;
    extern int window_height;

    bool load_config_file(sol::state& lua);
}

#endif //RETROGAMEENGINE_GLOBALCONFIG_H
