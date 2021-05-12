

#pragma once

#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief A base system of WAL
	class System
	{
	public:
		//! @brief A virtual, default, destructor
		virtual ~System() = default;
		
		//! @brief Get the name of the component corresponding to this system.
		virtual std::string getComponentName() const = 0;
		
		//! @brief Update the corresponding component of the given entity
		//! @param entity The entity to update.
		virtual void onUpdate(Entity &entity) = 0;
	protected:
		//! @brief A system can't be instantiated, it should be derived.
		System() = default;
		//! @brief A system can't be instantiated, it should be derived.
		System(const System &) = default;
		//! @brief A system can't be instantiated, it should be derived.
		System &operator=(const System &) = default;
	};
}