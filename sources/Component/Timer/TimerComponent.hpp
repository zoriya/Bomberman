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
		//! @brief Is the ticking of this component disabled?
		bool disabled = false;

		//! @brief The callback to call when the timer ring.
		WAL::Callback<WAL::Entity &, WAL::Wal &> callback;
		//! @brief The ring delay of this timer component.
		std::chrono::nanoseconds ringIn;

		Component *clone(WAL::Entity &entity) const override;

		//! @brief A default constructor
		TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay);
		//! @brief Create a timer with a callback.
		TimerComponent(WAL::Entity &entity, std::chrono::nanoseconds delay, const WAL::Callback<WAL::Entity &, WAL::Wal &> &timerCallback);
		//! @brief A timer component is copy constructable
		TimerComponent(const TimerComponent &) = default;
		//! @brief A default destructor
		~TimerComponent() override = default;
		//! @brief A component is not assignable.
		TimerComponent &operator=(const TimerComponent &) = delete;
	};
}
