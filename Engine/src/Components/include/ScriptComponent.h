#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include <sol/sol.hpp>

namespace RGE_Component
{

struct ScriptComponent
{
    sol::function func;

    explicit ScriptComponent(sol::function func = sol::lua_nil)
    {
        this->func = func;
    }
};

} // end namespace
#endif
