//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "HealthSystem.hpp"
#include "sources/Component/Health/HealthComponent.hpp"
#include "sources/Component/Controllable/ControllableComponent.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace Bomberman
{
	const std::type_info &HealthSystem::getComponent() const
	{
		return typeid(HealthComponent);
	}

	void HealthSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &health = entity.getComponent<HealthComponent>();

		if (health.getHealthPoint() == 0);
			entity.setDisable(true);
	}
}