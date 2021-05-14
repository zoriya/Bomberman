


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
	private:
		//! @brief The name of this component
		std::string _name;
		//! @brief Is this component disabled?
		bool _disabled = false;
	protected:
		//! @brief The entity that own this component
		Entity &_entity;
		//! @brief The list of dependencies of this component.
		std::vector<std::type_index> _dependencies;

		//! @brief A component can't be instantiated, it should be derived.
		explicit Component(std::string name, Entity &entity);
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

		//! @brief Get the name of this component
		std::string getName() const;

		//! @brief Used if the component is disabled 
		bool isDisabled() const;
		//! @brief Disable this component.
		void setDisable(bool disabled);

		//! @brief Get the dependencies of this component.
		const std::vector<std::type_index> &getDependencies() const;

		//! @brief The entity or this component has just been enabled.
		virtual void onStart();

		//! @brief The entity or this component has just been disable.
		virtual void onStop();
	};
}