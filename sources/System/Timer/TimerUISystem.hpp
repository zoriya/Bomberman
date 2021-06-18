//
// Created by Zoe Roux on 5/31/21.
//

#pragma once

#include <System/System.hpp>
#include <Wal.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Tag/TagComponent.hpp"

namespace BBM
{
	class TimerUISystem : public WAL::System<TimerComponent, Drawable2DComponent, TagComponent<"Timer">>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<TimerComponent, Drawable2DComponent, TagComponent<"Timer">> &entity, std::chrono::nanoseconds dtime) override;

		//! @brief A default constructor
		explicit TimerUISystem(WAL::Wal &);
		//! @brief A timer system is copy constructable.
		TimerUISystem(const TimerUISystem &) = default;
		//! @brief A default destructor
		~TimerUISystem() override = default;
		//! @breief A timer system is assignable.
		TimerUISystem &operator=(const TimerUISystem &) = delete;
	};
}
