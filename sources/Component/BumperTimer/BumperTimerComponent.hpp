//
// Created by Tom Augier on 2021-05-20.
//

#pragma once

#include <chrono>
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

using namespace std::chrono_literals;

namespace BBM
{
	class BumperTimerComponent : public WAL::Component
	{
		public:


			bool _isReseting = false;
			//! @brief The number of seconds of each refill. This variable is used to reset the nextBombRefill value.
			std::chrono::nanoseconds resetRate = 1500ms;
			//! @brief The number of nanosecond before the next bomb refill.
			std::chrono::nanoseconds nextReset = resetRate;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Constructor
			BumperTimerComponent(WAL::Entity &entity);

			//! @brief A BumperTimer component can't be instantiated, it should be derived.
			BumperTimerComponent(const BumperTimerComponent &) = default;

			//! @brief default destructor
			~BumperTimerComponent() override = default;

			//! @brief A BumperTimer component can't be assigned
			BumperTimerComponent &operator=(const BumperTimerComponent &) = delete;
	};
}