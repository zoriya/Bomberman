//
// Created by Benjamin Henry on 2021-06-01.
//

#include "BonusComponent.hpp"
#include <map>

namespace BBM {
	BonusComponent::BonusComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	WAL::Component *BonusComponent::clone(WAL::Entity &entity) const
	{
		return new BonusComponent(entity);
	}

	BonusComponent::BonusType BonusComponent::getRandomBonusType() const
	{
		double rnd = static_cast<double>(std::rand()) / RAND_MAX;

		if (rnd < 0.4)
			return (static_cast<BonusType>(std::rand() % (IGNOREWALLS - 1) + 1));
		return (NOTHING);
	}
}