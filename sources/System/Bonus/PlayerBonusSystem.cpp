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
		auto &playerBonus = entity.get<PlayerBonusComponent>();

		playerBonus.nextNoClipRate -= dtime;
		if (playerBonus.nextNoClipRate <= 0ns) {
			playerBonus.nextNoClipRate = playerBonus.noClipBonusRate;
			playerBonus.isNoClipOn = false;
		}
	}
}