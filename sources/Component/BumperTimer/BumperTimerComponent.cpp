//
// Created by Tom Augier on 2021-05-20.
//

#include "BumperTimerComponent.hpp"

namespace BBM
{
	BumperTimerComponent::BumperTimerComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	WAL::Component *BumperTimerComponent::clone(WAL::Entity &entity) const
	{
		return new BumperTimerComponent(entity);
	}
}