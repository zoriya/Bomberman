//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include <Component/Timer/TimerComponent.hpp>
#include "HealthSystem.hpp"
#include "Component/Health/HealthComponent.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	HealthSystem::HealthSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void HealthSystem::onFixedUpdate(WAL::ViewEntity<HealthComponent> &entity)
	{
		auto &health = entity.get<HealthComponent>();

		if (health.getHealthPoint() == 0) {
			health.onDeath(entity, this->_wal);
		}
	}
}