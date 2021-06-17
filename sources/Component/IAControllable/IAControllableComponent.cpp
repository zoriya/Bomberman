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
    IAControllableComponent::IAControllableComponent(WAL::Entity &entity, std::string scriptPath)
    : Component(entity), _scriptPath(scriptPath), _state()
    {
        if (std::filesystem::exists(scriptPath))
            _state.dofile(scriptPath);
    }

    WAL::Component *IAControllableComponent::clone(WAL::Entity &entity) const
	{
		return new IAControllableComponent(entity, _scriptPath);
	}

}
