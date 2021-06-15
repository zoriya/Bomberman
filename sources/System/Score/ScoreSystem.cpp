//
// Created by Tom Augier on 05/06/2021
//

#include "ScoreSystem.hpp"
#include <map>

namespace BBM {

	ScoreSystem::ScoreSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void ScoreSystem::onUpdate(WAL::ViewEntity<ScoreComponent, HealthComponent> &entity, std::chrono::nanoseconds dtime)
	{
		if (entity.get<HealthComponent>().getHealthPoint())
			entity.get<ScoreComponent>().aliveTime += dtime;
	}
}