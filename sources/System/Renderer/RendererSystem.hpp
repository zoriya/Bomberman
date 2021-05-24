//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "System/System.hpp"

namespace WAL
{
	class RendererSystem : public System
	{;

		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		void onUpdate(Entity &entity, std::chrono::nanoseconds dtime) override;

		//! @brief An alternative of onUpdate that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		//! @param entity The entity to update.
		void onFixedUpdate(Entity &entity) override;

		//! @brief A method called after all entities that this system manage has been updated.
		void onSelfUpdate() override;

	public:
		RendererSystem();
		RendererSystem(const RendererSystem &) = default;
		~RendererSystem() override = default;
		RendererSystem &operator=(const RendererSystem &) = default;
	};
}