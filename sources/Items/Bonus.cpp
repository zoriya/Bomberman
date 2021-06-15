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
		if (bonus.shouldDelete() || axis != CollisionComponent::CollidedAxis::ALL)
			return;
		auto *bombHolder = player.tryGetComponent<BombHolderComponent>();
		if (!bombHolder)
			return;
		bombHolder->maxBombCount++;
		std::cout << "BombHolder : " << bombHolder->maxBombCount << std::endl;
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
		std::cout << "BombRadius : " << bombHolder->explosionRadius << std::endl;
	}

	void Bonus::SpeedUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis)
	{
		if (bonus.shouldDelete() || axis != CollisionComponent::CollidedAxis::ALL)
			return;
		auto *controllable = player.tryGetComponent<ControllableComponent>();
		auto *playerBonus = player.tryGetComponent<PlayerBonusComponent>();
		if (!controllable || !playerBonus)
			return;
		controllable->speed += 0.05f;
		std::cout << "Speed : " << controllable->speed << std::endl;
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
	}

	Bonus::BonusType Bonus::getRandomBonusType()
	{
		double rnd = static_cast<double>(std::rand()) / RAND_MAX;

		std::cout << "Random" << rnd << std::endl;
		if (rnd <= 1)
			return (static_cast<BonusType>((std::rand() % NOCLIP) + 1));
		return (NOTHING);
	}
}