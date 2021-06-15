//
// Created by Tom Augier on 05/06/2021
//

#include "ScoreSystem.hpp"
#include <map>

namespace BBM {

	ScoreSystem::ScoreSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void ScoreSystem::onSelfUpdate()
	{
		ScoreComponent::Score maxScore = ScoreComponent::Score::PLAYING;

		for (auto &[_, score, _], this->_wal.getScene()->view<PositionComponent, CollisionComponent>())
	}
}