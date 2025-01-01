#include <iostream>
#include "Game/include/Game.h"

#include <lua/lua.hpp>
#include <sol/sol.hpp>

void TestLua()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    // Call lue code from script file
    lua.script_file("../Game/scripts/test.lua");
    // Same as above but an inline script
    lua.script("print('Hello World from Lua!')");

}

int main()
{
//    Game::Setup();
//    Game::Run();
//    Game::Destroy();

    TestLua();

    std::cout << "main.cpp exit" << std::endl;
    return 0;
}
