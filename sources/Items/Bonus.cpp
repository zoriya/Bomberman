//
// Created by HENRY Benjamin on 02/06/2021.
//

#include <Component/Collision/CollisionComponent.hpp>
#include <Component/Collision/CollisionComponent.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/Bonus/PlayerBonusComponent.hpp>
#include "Component/Movable/MovableComponent.hpp"
#include "Bonus.hpp"
#include <map>
#include <random>
#include "Component/BombHolder/BombHolderComponent.hpp"

namespace BBM {
	void Bonus::BombUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete() || axis != CollisionComponent::CollidedAxis::ALL)
			return;
		auto *bombHolder = player.tryGetComponent<BombHolderComponent>();
		if (!bombHolder)
			return;
		bombHolder->maxBombCount++;
		const_cast<WAL::Entity &>(bonus).scheduleDeletion();
	}

	void Bonus::ExplosionRangeBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete() || axis != CollisionComponent::CollidedAxis::ALL)
			return;
		auto *bombHolder = player.tryGetComponent<BombHolderComponent>();
		auto *playerBonus = player.tryGetComponent<PlayerBonusComponent>();
		if (!bombHolder || !playerBonus)
			return;
		bombHolder->explosionRadius++;
		const_cast<WAL::Entity &>(bonus).scheduleDeletion();
	}

	void Bonus::SpeedUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete() || axis != CollisionComponent::CollidedAxis::ALL)
			return;
		auto *controllable = player.tryGetComponent<ControllableComponent>();
		auto *playerBonus = player.tryGetComponent<PlayerBonusComponent>();
		if (!controllable || !playerBonus)
			return;
		controllable->speed += 0.025f;
		const_cast<WAL::Entity &>(bonus).scheduleDeletion();
	}

	void Bonus::NoClipBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete() || axis != CollisionComponent::CollidedAxis::ALL)
			return;
		auto *playerBonus = player.tryGetComponent<PlayerBonusComponent>();
		if (!playerBonus)
			return;
		playerBonus->nextNoClipRate = playerBonus->noClipBonusRate;
		playerBonus->isNoClipOn = true;
		const_cast<WAL::Entity &>(bonus).scheduleDeletion();
	}

	Bonus::BonusType Bonus::getRandomBonusType()
	{
		static std::default_random_engine generator(time(nullptr));
		std::map<BonusType, float> chanceValue = {
			{NOTHING, 100.0f},
			{SPEEDUP, 45.0f},
			{BOMBSTOCK, 30.0f},
			{EXPLOSIONINC, 15.0f},
			{NOCLIP, 1.5f},
		};
		std::uniform_int_distribution<int> distribution(1,1000);
		float value = (distribution(generator) / 10);
		BonusType bonus = NOTHING;

		for (auto &chance : chanceValue)
			if (chance.second > value)
				bonus = chance.first;
		return (bonus);
	}
}