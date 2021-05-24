//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "BombHolderComponent.hpp"

namespace BBM
{
	BombHolderComponent::BombHolderComponent(WAL::Entity &entity)
		: WAL::Component(entity),
		  _bombCount()
	{}

	BombHolderComponent::BombHolderComponent(WAL::Entity &entity, unsigned int maxBombCount)
		: WAL::Component(entity),
		  _bombCount(),
		  _maxBombCount(maxBombCount)
	{}

	WAL::Component *BombHolderComponent::clone(WAL::Entity &entity) const
	{
		return new BombHolderComponent(entity);
	}

	void BombHolderComponent::addBomb(unsigned int bombCount)
	{
		this->_bombCount += bombCount;
	}

	void BombHolderComponent::removeBomb(unsigned int damage)
	{
		if (damage >= this->_bombCount) {
			this->_bombCount = 0;
		} else
			this->_bombCount -= damage;
	}
}