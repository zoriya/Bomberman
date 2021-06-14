/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IAControllableComponent
*/

#include "Map/MapInfo.hpp"
#include "Component/IAControllable/IAControllableComponent.hpp"
//#include "System/IAControllable/IAControllableSystem.hpp"

namespace BBM
{
    IAControllableComponent::IAControllableComponent(WAL::Entity &entity, std::string scriptPath)
    : Component(entity), _scriptPath(scriptPath), state(luaL_newstate())
    {
        luaL_openlibs(state);
        
        luabridge::getGlobalNamespace(state)
            .beginNamespace ("luaBBM")
                .beginClass<MapInfo>("MapInfo")
                    .addProperty("x", &MapInfo::x)
                    .addProperty("y", &MapInfo::y)
                    .addProperty("z", &MapInfo::z)
                    .addProperty("type", &MapInfo::type)
                .endClass()
            .endNamespace();
        
        luaL_dofile(state, scriptPath.c_str());
    }

    WAL::Component *IAControllableComponent::clone(WAL::Entity &entity) const
	{
		return new IAControllableComponent(entity, _scriptPath);
	}

}
