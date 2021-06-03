/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IAComponent
*/

#include "IAComponent.hpp"
#include "lua.h"

namespace BBM
{
    IAComponent::IAComponent(WAL::Entity &entity, std::string scriptPath)
    : Component(entity),
     _scriptPath(scriptPath)
    { }

    IAComponent::IAComponent(WAL::Entity &entity)
    : Component(entity),
     _scriptPath()
    { }

    WAL::Component *IAComponent::clone(WAL::Entity &entity) const
	{
		return new IAComponent(entity);
	}

    Vector3f IAComponent::getPosition(void) const
    {
        return (this->_pos);
    }

    void IAComponent::setPosition(Vector3f &pos)
    {
        this->_pos = pos;
    }
}
