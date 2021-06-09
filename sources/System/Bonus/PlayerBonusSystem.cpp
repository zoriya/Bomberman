//
// Created by hbenjamin on 09/06/2021.
//

#include "PlayerBonusSystem.hpp"

using namespace std::chrono_literals;

namespace BBM
{
	PlayerBonusSystem::PlayerBonusSystem(WAL::Wal &wal)
			: System(wal)
	{}

	void PlayerBonusSystem::onUpdate(WAL::ViewEntity<PlayerBonusComponent, ControllableComponent, BombHolderComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &controllable = entity.get<ControllableComponent>();
		auto &holder = entity.get<BombHolderComponent>();
		auto &playerBonus = entity.get<PlayerBonusComponent>();

		playerBonus.nextSpeedBonusRate -= dtime;
		if (playerBonus.nextSpeedBonusRate <= 0ns) {
			playerBonus.nextSpeedBonusRate = playerBonus.speedBonusRate;
			controllable.speed = 0.25f;
		}
		playerBonus.nextDamageBonusRate -= dtime;
		if (playerBonus.nextDamageBonusRate <= 0ns) {
			playerBonus.nextDamageBonusRate = playerBonus.damageBonusRate;
			holder.damage = 1;
		}
		playerBonus.nextRangeBonusRate -= dtime;
		if (playerBonus.nextRangeBonusRate <= 0ns) {
			playerBonus.nextRangeBonusRate = playerBonus.rangeBonusRate;
			holder.explosionRadius = 3;
		}
	}
}