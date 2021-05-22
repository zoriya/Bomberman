//
// Created by Zoe Roux on 2021-05-14.
//

#pragma once

#include <chrono>
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief A base system of WAL
	class System
	{
	private:
		//! @brief The list of dependencies of this system
		std::vector<std::type_index> _dependencies = {};
	public:
		//! @brief A virtual, default, destructor
		virtual ~System() = default;
		//! @brief A system can be moved
		System(System &&) = default;

		//! @brief Get the name of the component corresponding to this system.
		const std::vector<std::type_index> &getDependencies() const;

		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		//! @param dtime The delta time.
		virtual void onUpdate(Entity &entity, std::chrono::nanoseconds dtime);

		//! @brief An alternative of onUpdate that is called every 8ms (120 times per seconds). If the system slow down, it will try to catch up.
		//! @remark This should be used for Physics, AI and everything that could be imprecise due to float rounding.
		//! @param entity The entity to update.
		virtual void onFixedUpdate(Entity &entity);

		//! @brief A method called after all entities that this system manage has been updated.
		virtual void onSelfUpdate();
	protected:
		//! @brief A system can't be instantiated, it should be derived.
		explicit System(std::vector<std::type_index> dependencies);
		//! @brief A system can't be instantiated, it should be derived.
		System(const System &) = default;
		//! @brief A system can't be instantiated, it should be derived.
		System &operator=(const System &) = default;
	};
}