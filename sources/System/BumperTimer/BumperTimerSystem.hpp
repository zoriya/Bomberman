//
// Created by Tom Augier on 2021-06-09.
//

#pragma once

#include "Component/Movable/MovableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/BumperTimer/BumperTimerComponent.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle BumperTimer entities.
	class BumperTimerSystem : public WAL::System<BumperTimerComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<BumperTimerComponent> &entity, std::chrono::nanoseconds dtime) override;
		//! @brief A default constructor
		explicit BumperTimerSystem(WAL::Wal &wal);
		//! @brief A BumperTimer system is copy constructable
		BumperTimerSystem(const BumperTimerSystem &) = default;
		//! @brief A default destructor
		~BumperTimerSystem() override = default;
		//! @brief A system is not assignable.
		BumperTimerSystem &operator=(const BumperTimerSystem &) = delete;
	};
}