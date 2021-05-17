//
// Created by Zoe Roux on 5/17/21.
//

#include "MovableComponent.hpp"

namespace WAL
{
	MovableComponent::MovableComponent(Entity &entity)
		: Component(entity)
	{}

	Component *MovableComponent::clone(Entity &entity) const
	{
		return new MovableComponent(entity);
	}

	void MovableComponent::addForce(Vector3f force)
	{
		this->_acceleration += force;
	}
}