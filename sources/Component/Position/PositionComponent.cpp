//
// Created by Zoe Roux on 5/17/21.
//

#include "PositionComponent.hpp"

namespace WAL
{
	PositionComponent::PositionComponent(Entity &entity)
		: Component(entity),
		  position()
	{}

	PositionComponent::PositionComponent(Entity &entity, Vector3f pos)
		: Component(entity),
		  position(pos)
	{}

	PositionComponent::PositionComponent(Entity &entity, float x, float y, float z)
		: Component(entity),
		  position(x, y, z)
	{}

	Component *PositionComponent::clone(WAL::Entity &entity) const
	{
		return new PositionComponent(entity, this->position);
	}

	float PositionComponent::getX() const
	{
		return this->position.x;
	}

	float PositionComponent::getY() const
	{
		return this->position.y;
	}

	float PositionComponent::getZ() const
	{
		return this->position.z;
	}
}