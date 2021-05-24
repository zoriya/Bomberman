//
// Created by Zoe Roux on 5/17/21.
//

#include "PositionComponent.hpp"
#include "Entity/Entity.hpp"
#include "Component/Component.hpp"

namespace BBM
{
	PositionComponent::PositionComponent(WAL::Entity &entity)
		: WAL::Component(entity),
		  position()
	{}

	PositionComponent::PositionComponent(WAL::Entity &entity, WAL::Vector3f pos)
		: WAL::Component(entity),
		  position(pos)
	{}

	PositionComponent::PositionComponent(WAL::Entity &entity, float x, float y, float z)
		: WAL::Component(entity),
		  position(x, y, z)
	{}

	WAL::Component *PositionComponent::clone(WAL::Entity &entity) const
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