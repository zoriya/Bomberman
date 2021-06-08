//
// Created by Benjamin Henry on 2021-06-01.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class BonusComponent : public WAL::Component
	{
		public:

			enum BonusType {
				NOTHING,
				BOMBSTOCK,
				SPEEDUP,
				EXPLOSIONINC,
				DAMAGEINC,
				IGNOREWALLS
			};

			std::chrono::nanoseconds disappearTimer = 5s;

			BonusType getRandomBonusType() const;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A Bonus component can't be instantiated, it should be derived.
			explicit BonusComponent(WAL::Entity &entity);

			//! @brief A Bonus component can't be instantiated, it should be derived.
			BonusComponent(const BonusComponent &) = default;

			//! @brief default destructor
			~BonusComponent() override = default;

			//! @brief A Bonus component can't be assigned
			BonusComponent &operator=(const BonusComponent &) = delete;
	};
}