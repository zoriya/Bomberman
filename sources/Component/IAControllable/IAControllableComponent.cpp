/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IAControllableComponent
*/

#include "IAControllableComponent.hpp"
#include "lua.h"

namespace BBM
{
    IAControllableComponent::IAControllableComponent(WAL::Entity &entity, std::string scriptPath)
    : Component(entity),
     _scriptPath(scriptPath)
    { }

    WAL::Component *IAControllableComponent::clone(WAL::Entity &entity) const
	{
		return new IAControllableComponent(entity, _scriptPath);
	}

}
