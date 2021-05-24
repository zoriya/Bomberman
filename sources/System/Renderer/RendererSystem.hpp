//
// Created by cbihan on 24/05/2021.
//

#pragma once

#include "System/System.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class RendererSystem : public WAL::System
	{

		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override;

		//! @brief An alternative of onUpdate that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		//! @param entity The entity to update.
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A method called after all entities that this system manage has been updated.
		void onSelfUpdate() override;

	public:
		RendererSystem();
		RendererSystem(const RendererSystem &) = default;
		~RendererSystem() override = default;
		RendererSystem &operator=(const RendererSystem &) = default;
	};
}