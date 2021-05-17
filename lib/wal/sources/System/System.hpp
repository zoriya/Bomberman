

#pragma once

#include <chrono>
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief A base system of WAL
	class System
	{
	public:
		//! @brief A virtual, default, destructor
		virtual ~System() = default;
		//! @brief A system can be moved
		System(System &&) = default;

		//! @brief Get the name of the component corresponding to this system.
		virtual std::type_info &getComponent() const = 0;
		
		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		virtual void onUpdate(Entity &entity, std::chrono::nanoseconds dtime) = 0;

		//! @brief An alternative of onUpdate that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		//! @param entity The entity to update.
		virtual void onFixedUpdate(Entity &entity) = 0;
	protected:
		//! @brief A system can't be instantiated, it should be derived.
		System() = default;
		//! @brief A system can't be instantiated, it should be derived.
		System(const System &) = default;
		//! @brief A system can't be instantiated, it should be derived.
		System &operator=(const System &) = default;
	};
}