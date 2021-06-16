
#pragma once

#include "System/System.hpp"
#include "Component/Score/ScoreComponent.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Wal.hpp"

namespace BBM
{
	class ScoreSystem : public WAL::System<ScoreComponent, HealthComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<ScoreComponent, HealthComponent> &entity, std::chrono::nanoseconds dtime) override;
		
		//! @brief ctor
		ScoreSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		ScoreSystem(const ScoreSystem &) = default;
		//! @brief Default dtor
		~ScoreSystem() override = default;
		//! @brief A SoundManager screen system can't be assigned.
		ScoreSystem &operator=(const ScoreSystem &) = delete;
	};
}
