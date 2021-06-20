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

	void ControllableComponent::disable()
	{
		this->disabled = true;
		this->pause = false;
		this->bomb = false;
		this->move = Vector2f();
	}
}