
#include "EndConditionSystem.hpp"
#include <map>
#include "Runner/Runner.hpp"
#include "Component/Score/ScoreComponent.hpp"

namespace BBM
{

	EndConditionSystem::EndConditionSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void EndConditionSystem::onSelfUpdate(std::chrono::nanoseconds dtime)
	{
		unsigned int alivePlayersCount = 0;
		auto &view = this->_wal.getScene()->view<ScoreComponent, HealthComponent>();

		if (!view.size())
			return;
		for (auto &[_, scoreComponent, healthComponent]: view)
			alivePlayersCount += (healthComponent.getHealthPoint() != 0);
		if (alivePlayersCount <= 1) {
			endConditionRate -= dtime;
			if (endConditionRate <= 0ns) {
				Runner::gameState.nextScene = Runner::gameState.ScoreScene;
				endConditionRate = 500ms;
			}
		}
	}
}