//
// Created by Zoe Roux on 2021-05-14.
//

#pragma once

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <memory>
#include "Component/Component.hpp"
#include "Exception/WalError.hpp"
#include "Wal.hpp"

namespace WAL
{

		class Scene {
		public:
			//! @brief Notify this scene that a component has been added to the given entity.
			//! @param entity The entity with the new component
			//! @param type The type of the component added.
			void _componentAdded(const Entity &entity, std::type_index type);
			//! @brief Notify this scene that a component has been removed to the given entity.
			//! @param entity The entity with the removed component
			//! @param type The type of the component removed.	namespace WAL
			void _componentRemoved(const Entity &entity, std::type_index type);
		};

	//! @brief An entity of the WAL's ECS.
	class Entity
	{
	private:
		//! @brief The unique ID of the entity
		unsigned _uid;
		//! @brief An entity name (this is useful for debugging)
		std::string _name;
		//! @brief Is this entity enabled?
		bool _disabled = false;
		//! @brief The list of the components of this entity
		std::unordered_map<std::type_index, std::unique_ptr<Component>> _components = {};

		//! @brief This ID will be the one of the next entity created.
		static unsigned nextID;
	protected:
		//! @brief A reference to the ECS.
		Scene &_scene;
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
		//! @throw NotFoundError if the component could not be found
		template<typename T>
		T &getComponent()
		{
			const std::type_index &type = typeid(T);
			auto existing = this->_components.find(type);
			if (existing == this->_components.end())
				throw NotFoundError("No component could be found with the type \"" + std::string(type.name()) + "\".");
			return *static_cast<T *>(existing->second.get());
		}

		//! @brief Check if this entity has a component.
		//! @tparam T The type of the component
		template<typename T>
		bool hasComponent() const
		{
			const std::type_info &type = typeid(T);
			return this->hasComponent(type);
		}

		//! @brief Check if this entity has a component.
		//! @param type The type of the component
		bool hasComponent(const std::type_info &type) const;

		//! @brief Check if this entity has a component.
		//! @param type The type of the component
		bool hasComponent(const std::type_index &type) const;

		//! @brief Add a component to this entity. The component is constructed in place.
		//! @throw DuplicateError is thrown if a component with the same type already exist.
		//! @return This entity is returned
		template<typename T, typename ...Types>
		Entity &addComponent(Types &&...params)
		{
			const std::type_index &type = typeid(T);
			if (this->hasComponent(type))
				throw DuplicateError("A component of the type \"" + std::string(type.name()) + "\" already exists.");
			this->_components[type] = std::make_unique<T>(*this, std::forward<Types>(params)...);
			this->_scene._componentAdded(*this, type);
			return *this;
		}

		//! @brief Copy a component to this entity.
		//! @return This entity is returned.
		Entity &addComponent(const Component &component);

		//! @brief Remove a specific component (by type).
		//! @throw NotFoundError is thrown if the component could not be found.
		//! @return This entity is returned.
		template<typename T>
		Entity &removeComponent()
		{
			const std::type_info &type = typeid(T);
			auto existing = this->_components.find(type);
			if (existing == this->_components.end())
				throw NotFoundError("No component could be found with the type \"" + std::string(type.name()) + "\".");
			this->_components.erase(existing);
			this->_scene._componentRemoved(*this, type);
			return *this;
		}

		//! @brief A default constructor
		explicit Entity(Scene &wal, std::string name);
		//! @brief An entity is copyable
		Entity(const Entity &);
		//! @brief An entity is movable.
		Entity(Entity &&) = default;
		//! @brief A default destructor
		~Entity() = default;
		//! @brief An entity is not assignable
		Entity &operator=(const Entity &) = delete;
	};
} // namespace WAL