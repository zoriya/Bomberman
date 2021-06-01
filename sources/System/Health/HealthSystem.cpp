//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "HealthSystem.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	HealthSystem::HealthSystem()
		: WAL::System({
			typeid(HealthComponent)
		})
	{}

	void HealthSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &health = entity.getComponent<HealthComponent>();

		if (health.getHealthPoint() == 0)
			health.onDeath(entity);
	}
}