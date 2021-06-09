//
// Created by HENRY Benjamin on 02/06/2021.
//

#include <Component/Collision/CollisionComponent.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/Bonus/PlayerBonusComponent.hpp>
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
			auto &playerBonus = player.getComponent<PlayerBonusComponent>();
			bombHolder.damage = 2;
			playerBonus.nextDamageBonusRate = playerBonus.damageBonusRate;
		}
	}

	void Bonus::ExplosionRangeBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		if (player.hasComponent<BombHolderComponent>()) {
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			auto &playerBonus = player.getComponent<PlayerBonusComponent>();
			if (bombHolder.explosionRadius <= 6)
				bombHolder.explosionRadius++;
			playerBonus.nextRangeBonusRate = playerBonus.rangeBonusRate;
		}
	}

	void Bonus::SpeedUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		if (!player.hasComponent<MovableComponent>())
			return;
		auto &controllable = player.getComponent<ControllableComponent>();
		auto &playerBonus = player.getComponent<PlayerBonusComponent>();
		controllable.speed = 0.35f;
		playerBonus.nextSpeedBonusRate = playerBonus.speedBonusRate;
	}

	void Bonus::IgnoreWallsBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		if (player.hasComponent<BombHolderComponent>()) {
			auto &playerBonus = player.getComponent<PlayerBonusComponent>();
			auto &bombHolder = player.getComponent<BombHolderComponent>();
			playerBonus.nextIgnoreWallsBonusRate = playerBonus.ignoreWallsBonusRate;
			std::cout << "Explosion is supposed to pass through walls here" << std::endl;
			//bombHolder.ignoreWalls = true;
		}
	}
}