//
// Created by Tom Augier on 2021-06-09.
//

#include "BumperTimerSystem.hpp"

namespace BBM
{
	BumperTimerSystem::BumperTimerSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void BumperTimerSystem::onUpdate(WAL::ViewEntity<BumperTimerComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &bumperTimer = entity.get<BumperTimerComponent>();

		if (bumperTimer._isReseting) {
			bumperTimer.nextReset -= dtime;
			if (bumperTimer.nextReset <= 0ns) {
				bumperTimer.nextReset = bumperTimer.resetRate;
				bumperTimer._isReseting = false;
			}
		}
	}
}