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

	HealthComponent::HealthComponent(WAL::Entity &entity, unsigned int healthPoint)
		: WAL::Component(entity),
		  _healthPoint(healthPoint)
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
		if (damage >= this->_healthPoint)
			this->die();
		else
			this->_healthPoint -= damage;
	}

	void HealthComponent::die(void)
	{
		this->setDisable(true);
	}
}