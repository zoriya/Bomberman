//
// Created by HENRY Benjamin on 02/06/2021.
// Edited by AUGIER Tom on 02/06/2021.
//

#pragma once

#include "Entity/Entity.hpp"

namespace BBM {
	class Bonus {
	public:
		//! @param bonus bonus
		//! @param player the entity on which the effect will be applied
		//! @brief Apply bonus effect that allows players to carry one more bomb than before
		static void BombUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis);

		//! @param bonus bonus
		//! @param player the entity on which the effect will be applied
		//! @brief Apply bonus effect who increased the bomb damage
		static void DamageIncreasedBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis);

		//! @param bonus bonus
		//! @param player the entity on which the effect will be applied
		//! @brief Apply bonus effect that expend the explosion range of the bomb
		static void ExplosionRangeBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis);

		//! @param bonus bonus
		//! @param player the entity on which the effect will be applied
		//! @brief Apply bonus effect that allows to run faster
		static void SpeedUpBonus(WAL::Entity &player, const WAL::Entity &bonus, CollisionComponent::CollidedAxis axis);

		enum BonusType {
			NOTHING,
			BOMBSTOCK,
			SPEEDUP,
			EXPLOSIONINC,
			DAMAGEINC
		};

		static BonusType getRandomBonusType();
	};
}