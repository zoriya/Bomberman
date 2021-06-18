//
// Created by cbihan on 18/06/2021.
//

#include "SpeedComponent.hpp"

namespace BBM
{
	SpeedComponent::SpeedComponent(WAL::Entity &entity) :
		WAL::Component(entity)
	{
	}

	WAL::Component *SpeedComponent::clone(WAL::Entity &entity) const
	{
		return new SpeedComponent(this->_entity, this->speed);
	}

	SpeedComponent::SpeedComponent(WAL::Entity &entity, float entitySpeed) :
		WAL::Component(entity),
		speed(entitySpeed)
	{
	}
}