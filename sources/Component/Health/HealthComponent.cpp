//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "HealthComponent.hpp"

namespace BBM
{
	HealthComponent::HealthComponent(WAL::Entity &entity)
		: WAL::Component(entity),
		  _healthPoint()
	{}

	HealthComponent::HealthComponent(WAL::Entity &entity, unsigned int healthPoint, WAL::Callback<WAL::Entity &> onDeath)
		: WAL::Component(entity),
		  _healthPoint(healthPoint),
		  onDeath(onDeath)
	{}

	WAL::Component *HealthComponent::clone(WAL::Entity &entity) const
	{
		return new HealthComponent(entity);
	}

	void HealthComponent::addHealthPoint(unsigned int healthPoint)
	{
		this->_healthPoint += healthPoint;
	}

	void HealthComponent::takeDmg(unsigned int damage)
	{
		if (damage >= this->_healthPoint) {
			this->_healthPoint = 0;
 		} else
			this->_healthPoint -= damage;
	}

	unsigned int HealthComponent::getHealthPoint(void) const
	{
		return (this->_healthPoint);
	}
}