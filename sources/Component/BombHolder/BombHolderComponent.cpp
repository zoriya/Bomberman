//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "BombHolderComponent.hpp"

namespace BBM
{
	BombHolderComponent::BombHolderComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	BombHolderComponent::BombHolderComponent(WAL::Entity &entity, unsigned int maxCount)
		: WAL::Component(entity),
		  maxBombCount(maxCount)
	{}

	WAL::Component *BombHolderComponent::clone(WAL::Entity &entity) const
	{
		return new BombHolderComponent(entity, this->maxBombCount);
	}
}