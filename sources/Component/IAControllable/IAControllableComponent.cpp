/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IAControllableComponent
*/

#include <filesystem>
#include "Map/MapInfo.hpp"
#include "Component/IAControllable/IAControllableComponent.hpp"

namespace BBM
{
    auto a = [](lua_State *L) -> int
    {
        const int *pThis = (const int*) lua_topointer(L, lua_upvalueindex(1));
        //const float x = lua_tonumber(state, -1);
        std::cout << *pThis;
        return 0;
    };
    IAControllableComponent::IAControllableComponent(WAL::Entity &entity, std::string scriptPath)
    : Component(entity), _scriptPath(scriptPath), _state(), registered(false)
    {
        static int x = 1;
        lua_pushlightuserdata(_state.getState(), &x);
        //lua_pushnumber(state, x);
        lua_pushcclosure(_state.getState(), a, 1);
        lua_setglobal(_state.getState(), "a");
        x++;
        if (std::filesystem::exists(scriptPath))
            _state.dofile(scriptPath);

    }

    WAL::Component *IAControllableComponent::clone(WAL::Entity &entity) const
	{
		return new IAControllableComponent(entity, _scriptPath);
	}

}
