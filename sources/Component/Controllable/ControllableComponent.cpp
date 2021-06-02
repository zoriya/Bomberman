//
// Created by Zoe Roux on 5/24/21.
//

#include "ControllableComponent.hpp"

namespace BBM
{
	ControllableComponent::ControllableComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	WAL::Component *ControllableComponent::clone(WAL::Entity &entity) const
	{
		return new ControllableComponent(entity);
	}
}