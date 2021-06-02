//
// Created by HENRY Benjamin on 02/06/2021.
//

#pragma once

#include "Entity/Entity.hpp"

namespace BBM {
	class Bonus {
	public:
		static void BombUpBonus(const WAL::Entity &entity, const WAL::Entity &other);
		static void DamageIncreasedBonus(const WAL::Entity &entity, const WAL::Entity &other);
		static void ExplosionRangeBonus(const WAL::Entity &entity, const WAL::Entity &other);
		static void SpeedUpBonus(const WAL::Entity &entity, const WAL::Entity &other);
		static void IgnoreWallsBonus(const WAL::Entity &entity, const WAL::Entity &other);
	};
}