
#pragma once

#include "System/System.hpp"
#include "Component/Score/ScoreComponent.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Wal.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class EndConditionSystem : public WAL::System<ScoreComponent, HealthComponent>
	{
	public:
		std::chrono::nanoseconds endConditionRate = 500ms;

		//! @inherit
		void onSelfUpdate(std::chrono::nanoseconds dtime) override;
		
		//! @brief ctor
		EndConditionSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		EndConditionSystem(const EndConditionSystem &) = default;
		//! @brief Default dtor
		~EndConditionSystem() override = default;
		//! @brief A SoundManager screen system can't be assigned.
		EndConditionSystem &operator=(const EndConditionSystem &) = delete;
	};
}
