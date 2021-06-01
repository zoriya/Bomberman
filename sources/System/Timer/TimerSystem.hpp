//
// Created by Zoe Roux on 5/31/21.
//

#pragma once

#include <System/System.hpp>
#include <Wal.hpp>

namespace BBM
{
	class TimerSystem : public WAL::System
	{
	private:
		//! @brief The wal engine
		WAL::Wal &_wal;
	public:
		//! @inherit
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override;

		//! @brief A default constructor
		TimerSystem(WAL::Wal &);
		//! @brief A timer system is copy constructable.
		TimerSystem(const TimerSystem &) = default;
		//! @brief A default destructor
		~TimerSystem() override = default;
		//! @breief A timer system is assignable.
		TimerSystem &operator=(const TimerSystem &) = default;
	};
}
