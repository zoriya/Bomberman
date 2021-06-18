//
// Created by Zoe Roux on 5/31/21.
//

#include "TimerSystem.hpp"
#include "Component/Timer/TimerComponent.hpp"
#include "Drawables/2D/Text.hpp"

using namespace std::chrono_literals;

namespace BBM
{
	TimerSystem::TimerSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void TimerSystem::onUpdate(WAL::ViewEntity<TimerComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &timer = entity.get<TimerComponent>();
		timer.ringIn -= dtime;
		if (timer.ringIn <= 0ns) {
			timer.callback(entity, this->_wal);
		}
	}
}