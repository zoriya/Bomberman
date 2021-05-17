//
// Created by Zoe Roux on 5/17/21.
//

#include "PositionComponent.hpp"

namespace WAL::Components
{
	PositionComponent::PositionComponent(Entity &entity)
		: Component(entity),
		_position()
	{}

	PositionComponent::PositionComponent(Entity &entity, Vector3f pos)
		: Component(entity),
		  _position(pos)
	{}

	PositionComponent::PositionComponent(Entity &entity, float x, float y, float z)
		: Component(entity),
		_position(x, y, z)
	{}

	Component *PositionComponent::clone(WAL::Entity &entity) const
	{
		return new PositionComponent(entity, this->_position);
	}

	Vector3f &PositionComponent::getPosition()
	{
		return this->_position;
	}

	const Vector3f &PositionComponent::getPosition() const
	{
		return this->_position;
	}

	float PositionComponent::getX() const
	{
		return this->_position.x;
	}

	float PositionComponent::getY() const
	{
		return this->_position.y;
	}

	float PositionComponent::getZ() const
	{
		return this->_position.z;
	}
}