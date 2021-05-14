

#pragma once

#include <string>
#include <vector>
#include "Component/Component.hpp"

namespace WAL
{
	//! @brief An entity of the WAL's ECS.
	class Entity
	{
	private:
		//! @brief The unique ID of the entity
		unsigned _uid;
		//! @brief An entity name (this is useful for debugging)
		std::string _name;
		//! @brief Is this entity enabled?
		bool _disabled;
		//! @brief The list of the components of this entity
		std::vector<Component> _components;
	public:
		//! @brief Get the ID of the entity.
		unsigned getUid() const;
		//! @brief Get the name fo the entity
		std::string getName() const;

		//! @brief Used if the entity is disabled 
		bool isDisable() const;

		//! @brief Disable this entity.
		void setDisable(bool disabled);

		//! @brief Get a component of a specific type
		//! @throw ComponentNotFoundError if the component could not be found
		template<typename T>
		T getComponent();

		//! @brief Add a component to this entity. The component is constructed in place.
		//! @return This entity is returned
		template<typename T, ...Types>
		Entity &addComponent(Types ...params);

		//! @brief Copy a component to this entity.
		//! @return This entity is returned.
		Entity &addComponent(const Component &component);

		//! @brief Remove a specific component (by type).
		template<typename T>
		Entity &removeComponent();

		//! @brief A default constructor
		Entity(const std::string &name);
		//! @brief An entity is copyable
		Entity(const Entity &);
		//! @brief A default destructor
		~Entity() = default;
		//! @brief An entity is assignable
		Entity &operator=(const Entity &);
	};
}