//
// Created by Zoe Roux on 5/31/21.
//

#pragma once

#include <System/System.hpp>
#include <Wal.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include "Component/Renderer/Drawable2DComponent.hpp"

namespace BBM
{
	class TimerSystem : public WAL::System<TimerComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<TimerComponent> &entity, std::chrono::nanoseconds dtime) override;

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
