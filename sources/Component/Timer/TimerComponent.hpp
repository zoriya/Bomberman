//
// Created by Zoe Roux on 5/31/21.
//

#pragma once

#include <Component/Component.hpp>
#include <chrono>
#include <Wal.hpp>
#include "Models/Callback.hpp"

namespace BBM
{
	//! @brief
	class TimerComponent : public WAL::Component
	{
	public:
		//! @brief The callback to call when the timer ring.
		WAL::Callback<WAL::Entity &, const WAL::Wal &> callback;
		//! @brief The ring delay of this timer component.
		std::chrono::nanoseconds ringIn;

		Component *clone(WAL::Entity &entity) const override;

		//! @brief A default constructor
		TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay);
		//! @brief Create a timer with a callback.
		TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay, const WAL::Callback<WAL::Entity &, const WAL::Wal &> &callback);
		//! @brief Create a timer with a function to call on ring.
		TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay, std::function<void (WAL::Entity &, const WAL::Wal &)> callback);
		//! @brief A timer component is copy constructable
		TimerComponent(const TimerComponent &) = default;
		//! @brief A default destructor
		~TimerComponent() override = default;
		//! @brief A component is not assignable.
		TimerComponent &operator=(const TimerComponent &) = delete;
	};
}
