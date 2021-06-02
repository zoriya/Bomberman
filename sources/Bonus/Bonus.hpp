//
// Created by HENRY Benjamin on 02/06/2021.
// Edited by AUGIER Tom on 02/06/2021.
//

#pragma once

#include "Entity/Entity.hpp"

namespace BBM {
	class Bonus {
	public:
		//! @param entity bonus
		//! @param other the entity on which the effect will be applied
		//! @brief Apply bonus effect that allows players to carry one more bomb than before
		static void BombUpBonus(const WAL::Entity &entity, const WAL::Entity &other);

		//! @param entity bonus
		//! @param other the entity on which the effect will be applied
		//! @brief Apply bonus effect who increased the bomb damage
		static void DamageIncreasedBonus(const WAL::Entity &entity, const WAL::Entity &other);

		//! @param entity bonus
		//! @param other the entity on which the effect will be applied
		//! @brief Apply bonus effect that expend the explosion range of the bomb
		static void ExplosionRangeBonus(const WAL::Entity &entity, const WAL::Entity &other);

		//! @param entity bonus
		//! @param other the entity on which the effect will be applied
		//! @brief Apply bonus effect that allows to run faster
		static void SpeedUpBonus(const WAL::Entity &entity, const WAL::Entity &other);

		//! @param entity bonus
		//! @param other the entity on which the effect will be applied
		//! @brief Apply bonus effect that allows bomb explosion to pass through walls
		static void IgnoreWallsBonus(const WAL::Entity &entity, const WAL::Entity &other);
	};
}