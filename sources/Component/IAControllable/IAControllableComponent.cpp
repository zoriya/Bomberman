/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IAControllableComponent
*/

#include "Component/IAControllable/IAControllableComponent.hpp"

namespace BBM
{
    IAControllableComponent::IAControllableComponent(WAL::Entity &entity, std::string scriptPath)
    : Component(entity), _scriptPath(scriptPath), state(luaL_newstate())
    {
        luaL_dofile(state, scriptPath.c_str());
        lua_getglobal(state, "Update");
        if (!lua_isfunction(state, -1))
            std::cout << "No update function in the script" << std::endl;
    }

    WAL::Component *IAControllableComponent::clone(WAL::Entity &entity) const
	{
		return new IAControllableComponent(entity, _scriptPath);
	}

}
