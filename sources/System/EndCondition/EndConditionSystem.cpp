
#include "EndConditionSystem.hpp"
#include <map>
#include "Runner/Runner.hpp"

namespace BBM {

	EndConditionSystem::EndConditionSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void EndConditionSystem::onSelfUpdate()
	{
		unsigned int alivePlayersCount = 0;

        for (auto & [_ , healthComponent]: this->_wal.getScene()->view<HealthComponent>())
            alivePlayersCount += (healthComponent.getHealthPoint() != 0);
        if (alivePlayersCount <= 1)
            Runner::gameState.nextScene = Runner::gameState.MainMenuScene;
	}
}