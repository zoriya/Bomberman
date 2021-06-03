//
// Created by HENRY Benjamin on 02/06/2021.
//

#include "Component/Movable/MovableComponent.hpp"
#include "Bonus.hpp"
//#include "Component/BombHolderComponent/BombHolderComponent.hpp"

namespace BBM {
	void Bonus::BombUpBonus(WAL::Entity &player, const WAL::Entity &bonus)
	{
		/* if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			bombHolder.maxBombCount++;
		} */
	}

	void Bonus::DamageIncreasedBonus(WAL::Entity &player, const WAL::Entity &bonus)
	{
		/* if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			bombHolder.damage++;
		} */
	}

	void Bonus::ExplosionRangeBonus(WAL::Entity &player, const WAL::Entity &bonus)
	{
		/* if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			bombHolder.explosionRange++;
		} */
	}

	void Bonus::SpeedUpBonus(WAL::Entity &player, const WAL::Entity &bonus)
	{
		if (!player.hasComponent<MovableComponent>())
			return;
		auto &movable = player.getComponent<MovableComponent>();
		movable.addForce(Vector3f(1, 0, 1));
	}

	void Bonus::IgnoreWallsBonus(WAL::Entity &player, const WAL::Entity &bonus)
	{
		/* if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			bombHolder.ignoreWalls = true;
		} */
	}
}