//
// Created by HENRY Benjamin on 02/06/2021.
//

#include "Component/Movable/MovableComponent.hpp"
#include "Bonus.hpp"
//#include "Component/BombHolderComponent/BombHolderComponent.hpp"

namespace BBM {
	void Bonus::BombUpBonus(WAL::Entity &entity, const WAL::Entity &other)
	{
		//auto &bombHolder = entity.getComponent<BombHolderComponent>();
		//bombHolder.maxBombCount++;
		//other.scheduleDeletion(true);
	}

	void Bonus::DamageIncreasedBonus(WAL::Entity &entity, const WAL::Entity &other)
	{
		//auto &bombHolder = entity.getComponent<BombHolderComponent>();
		//bombHolder.damage++;
		//other.scheduleDeletion(true);
	}

	void Bonus::ExplosionRangeBonus(WAL::Entity &entity, const WAL::Entity &other)
	{
		//auto &bombHolder = entity.getComponent<BombHolderComponent>();
		//bombHolder.explosionRange++;
		//other.scheduleDeletion(true);
	}

	void Bonus::SpeedUpBonus(WAL::Entity &entity, const WAL::Entity &other)
	{
		auto &movable = entity.getComponent<MovableComponent>();
		movable.addForce(Vector3f(1, 0, 1));
		//other.scheduleDeletion(true);
	}

	void Bonus::IgnoreWallsBonus(WAL::Entity &entity, const WAL::Entity &other)
	{
		//auto &bombHolder = entity.getComponent<BombHolderComponent>();
		//bombHolder.ignoreWall = false;
		//other.scheduleDeletion(true);
	}
}