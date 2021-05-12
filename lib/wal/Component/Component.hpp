


#pragma once

#include <vector>
#include <string>

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
		bool _disabled;
		//! @brief The list of dependencies of this component.
		// TODO check if there is a better type than strings
		std::vector<std::string> _dependencies;
	public:
		//! @brief Get the name of this component
		std::string _getName() const;

		//! @brief Used if the component is disabled 
		bool isDisable() const;
		//! @brief Disable this component.
		void setDisable(bool disabled);

		//! @brief The entity or this component has just been enabled.
		//! @param entity The entity that has this component
		virtual void onStart(Entity &entity);

		//! @brief The entity or this component has just been disable.
		//! @param entity The entity that has this component
		virtual void onStop(Entity &entity);

		//! @brief A virtual destructor (that also calls onStop)
		virtual ~Component();
	protected:
		//! @brief A component can't be instantiated, it should be derived.
		Component() = default;
		//! @brief A component can't be instantiated, it should be derived.
		Component(const Component &) = default;
		//! @brief A component can't be instantiated, it should be derived.
		Component &operator=(const Component &) = default;
	};
}