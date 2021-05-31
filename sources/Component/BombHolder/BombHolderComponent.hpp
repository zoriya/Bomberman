//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class BombHolderComponent : public WAL::Component
	{
		public:
			//! @brief The number of bomb that this entity hold.
			unsigned int bombCount = 1;
			//! @brief The max number of  bomb that this entity can have.
			unsigned int maxBombCount = 3;
			//! @brief The number of seconds of each refill. This variable is used to reset the nextBombRefill value.
			std::chrono::nanoseconds refillRate = 5000ns;
			//! @brief The number of nanosecond before the next bomb refill.
			std::chrono::nanoseconds nextBombRefill = refillRate;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A component can't be instantiated, it should be derived.
			explicit BombHolderComponent(WAL::Entity &entity);

			//! @brief Constructor
			BombHolderComponent(WAL::Entity &entity, unsigned int maxBombCount);

			//! @brief A component can't be instantiated, it should be derived.
			BombHolderComponent(const BombHolderComponent &) = default;

			//! @brief default destructor
			~BombHolderComponent() override = default;

			//! @brief A component can't be assigned
			BombHolderComponent &operator=(const BombHolderComponent &) = delete;
	};
}