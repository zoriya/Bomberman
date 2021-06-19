//
// Created by hbenjamin on 09/06/2021.
//

#include "PlayerBonusSystem.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Health//HealthComponent.hpp"
#include "Component/Tag/TagComponent.hpp"
#include "Component/Collision/CollisionComponent.hpp"

using namespace std::chrono_literals;

namespace BBM
{
	PlayerBonusSystem::PlayerBonusSystem(WAL::Wal &wal)
			: System(wal)
	{}

	void PlayerBonusSystem::onUpdate(WAL::ViewEntity<PlayerBonusComponent, ControllableComponent, BombHolderComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &playerBonus = entity.get<PlayerBonusComponent>();

		playerBonus.nextNoClipRate -= dtime;
		if (playerBonus.nextNoClipRate <= 0ns && playerBonus.isNoClipOn) {
			playerBonus.nextNoClipRate = playerBonus.noClipBonusRate;
			playerBonus.isNoClipOn = false;
			auto playerPos = entity->tryGetComponent<PositionComponent>();
			auto playerHealth = entity->tryGetComponent<HealthComponent>();
			if (!playerHealth || !playerPos)
				return;
			for (auto &[other, pos, _] : this->_wal.getScene()->view<PositionComponent, TagComponent<Blowable>>()) {
				auto vec = (playerPos->position - pos.position).abs();
				if (vec.x < 0.65   && vec.z < 0.65 && playerPos->position.distance(pos.position) < 1)
					playerHealth->takeDmg(playerHealth->getHealthPoint());
			}
		}
	}
}