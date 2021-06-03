//
// Created by Zoe Roux on 2021-06-04.
//


#pragma once

#include "Entity/Entity.hpp"
#include "View/View.hpp"
#include <chrono>

namespace WAL
{
	//! @brief A base class that represent a system.
	class ISystem
	{
	public:
		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		virtual void onUpdate(Entity &entity, std::chrono::nanoseconds dtime) = 0;

		//! @brief An alternative of onUpdate that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		//! @param entity The entity to update.
		virtual void onFixedUpdate(Entity &entity) = 0;

		//! @brief A method called after all entities that this system manage has been updated.
		virtual void onSelfUpdate() = 0;

		//! @brief Get a view containing every entity this system should update.
		virtual BaseView &getView() = 0;

		//! @brief A virtual default destructor.
		virtual ~ISystem() = default;
	};
}