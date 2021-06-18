//
// Created by Zoe Roux on 5/24/21.
//

#include "ControllableComponent.hpp"

namespace BBM
{
	ControllableComponent::ControllableComponent(WAL::Entity &entity)
		: WAL::Component(entity),
		disabled(false)
	{}

	WAL::Component *ControllableComponent::clone(WAL::Entity &entity) const
	{
		return new ControllableComponent(entity);
	}

	ControllableComponent::ControllableComponent(WAL::Entity &entity, bool isDisabled)
		: WAL::Component(entity),
		disabled(isDisabled)
	{}
}