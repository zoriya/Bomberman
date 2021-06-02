//
// Created by Benjamin Henry on 2021-06-01.
//

#include "BonusComponent.hpp"

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
		return (static_cast<BonusType>(std::rand() % IGNOREWALLS));
	}
}