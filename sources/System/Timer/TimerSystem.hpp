//
// Created by Zoe Roux on 5/31/21.
//

#pragma once

#include <System/System.hpp>

namespace BBM
{
	class TimerSystem : public WAL::System
	{
	public:
		//! @inherit
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override;

		//! @brief A default constructor
		TimerSystem();
		//! @brief A timer system is copy constructable.
		TimerSystem(const TimerSystem &) = default;
		//! @brief A default destructor
		~TimerSystem() override = default;
		//! @breief A timer system is assignable.
		TimerSystem &operator=(const TimerSystem &) = default;
	};
}
