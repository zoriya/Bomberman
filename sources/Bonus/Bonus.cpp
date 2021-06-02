//
// Created by HENRY Benjamin on 02/06/2021.
//

#include "Bonus.hpp"
//#include "Component/BombHolderComponent/BombHolderComponent.hpp"

namespace BBM {
	void Bonus::BombUpBonus(const WAL::Entity &entity, const WAL::Entity &other)
	{
		auto &bombHolder = other.getComponent<BombHolderComponent>();
		bombHolder.maxBombCount++;
	}

	void Bonus::DamageIncreasedBonus(const WAL::Entity &entity, const WAL::Entity &other)
	{
		auto &bombHolder = other.getComponent<BombHolderComponent>();
		//bombHolder.damage++;
	}

	void Bonus::ExplosionRangeBonus(const WAL::Entity &entity, const WAL::Entity &other)
	{
		auto &bombHolder = other.getComponent<BombHolderComponent>();
		//bombHolder.explosionRange++;
	}

	void Bonus::SpeedUpBonus(const WAL::Entity &entity, const WAL::Entity &other)
	{
		auto &movable = other.getComponent<MovableComponent>();
		movable.addForce(Vector3f(1, 0, 1));
	}

	void Bonus::IgnoreWallsBonus(const WAL::Entity &entity, const WAL::Entity &other)
	{
		auto &bombHolder = other.getComponent<BombHolderComponent>();
		//bombHolder.ignoreWall = false;
	}
}