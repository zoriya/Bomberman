//
// Created by HENRY Benjamin on 02/06/2021.
//

#include <Component/Collision/CollisionComponent.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include "Component/Movable/MovableComponent.hpp"
#include "Bonus.hpp"
#include "Component/BombHolder/BombHolderComponent.hpp"

namespace BBM {
	void Bonus::BombUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			bombHolder.maxBombCount++;
		}
	}

	void Bonus::DamageIncreasedBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			bombHolder.damage++;
		}
	}

	void Bonus::ExplosionRangeBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			bombHolder.explosionRadius++;
		}
	}

	void Bonus::SpeedUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		if (!player.hasComponent<MovableComponent>())
			return;
		auto &controllable = player.getComponent<ControllableComponent>();
		controllable.speed = 0.35f;
		controllable.nextSpeedBonusRate = controllable.speedBonusRate;
	}

	void Bonus::IgnoreWallsBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			std::cout << "Explosion is supposed to pass through walls here" << std::endl;
			//bombHolder.ignoreWalls = true;
		}
	}
}