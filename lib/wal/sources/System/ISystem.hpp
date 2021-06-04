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
		//! @brief Update the whole system (every entities that this system is responsible can be updated.
		//! @param dtime The delta time since the last call to this method.
		virtual void update(std::chrono::nanoseconds dtime) = 0;

		//! @brief An alternative of update that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		virtual void fixedUpdate() = 0;

		//! @brief Get a view containing every entity this system should update.
		virtual IView &getView() = 0;

		//! @brief A virtual default destructor.
		virtual ~ISystem() = default;
	};
}