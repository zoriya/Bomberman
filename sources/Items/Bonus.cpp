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
		auto *bombHolder = player.tryGetComponent<BombHolderComponent>();
		if (bombHolder == nullptr)
			return;
		bombHolder->maxBombCount++;
	}

	void Bonus::DamageIncreasedBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		auto *bombHolder = player.tryGetComponent<BombHolderComponent>();
		if (bombHolder == nullptr)
			return;
		auto &playerBonus = player.getComponent<PlayerBonusComponent>();
		bombHolder->damage = 2;
		playerBonus.nextDamageBonusRate = playerBonus.damageBonusRate;
	}

	void Bonus::ExplosionRangeBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		auto *bombHolder = player.tryGetComponent<BombHolderComponent>();
		if (bombHolder == nullptr)
			return;
		auto &playerBonus = player.getComponent<PlayerBonusComponent>();
		if (bombHolder->explosionRadius <= 6)
			bombHolder->explosionRadius++;
		playerBonus.nextRangeBonusRate = playerBonus.rangeBonusRate;
	}

	void Bonus::SpeedUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete())
			return;
		auto *controllable = player.tryGetComponent<ControllableComponent>();
		auto &playerBonus = player.getComponent<PlayerBonusComponent>();
		controllable->speed = 0.35f;
		playerBonus.nextSpeedBonusRate = playerBonus.speedBonusRate;
	}

	Bonus::BonusType Bonus::getRandomBonusType()
	{
		double rnd = static_cast<double>(std::rand()) / RAND_MAX;

		if (rnd < 0.4)
			return (static_cast<BonusType>(std::rand() % (DAMAGEINC - 1) + 1));
		return (NOTHING);
	}
}