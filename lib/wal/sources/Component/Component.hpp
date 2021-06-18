//
// Created by Zoe Roux on 2021-05-14.
//

#pragma once

#include <vector>
#include <string>
#include <typeindex>

namespace WAL
{
	//! @brief The entity class, used to prevent circular dependencies.
	class Entity;

	//! @brief Represent a single component of WAL.
	class Component
	{
	protected:
		//! @brief The entity that own this component
		Entity &_entity;

		//! @brief A component can't be instantiated, it should be derived.
		explicit Component(Entity &entity);
		//! @brief A component can't be instantiated, it should be derived.
		Component(const Component &) = default;
	public:
		//! @brief A component can't be assigned
		Component &operator=(const Component &) = delete;
		//! @brief A virtual destructor
		virtual ~Component() = default;

		//! @brief Clone a component for another or the same entity.
		//! @param entity The entity that owns the ne component.
		virtual Component *clone(Entity &entity) const = 0;

		//! @brief The entity or this component has just been enabled.
		virtual void onStart();

		//! @brief The entity or this component has just been disable.
		virtual void onStop();
	};
} // namespace WAL