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
#include "Models/TypeHolder.hpp"

namespace WAL
{
	class Scene;

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
		//! @brief Has this entity been scheduled for deletion?
		bool _shouldDelete = false;
		//! @brief Should this entity notify the scene of component changes?
		bool _notifyScene;
		//! @brief The list of the components of this entity
		std::unordered_map<std::type_index, std::unique_ptr<Component>> _components = {};

		//! @brief This ID will be the one of the next entity created.
		static unsigned nextID;

		//! @brief Callback called when a component is added
		//! @param type The type of component
		void _componentAdded(const std::type_index &type);
		//! @brief Callback called when a component is removed
		//! @param type The type of component
		void _componentRemoved(const std::type_index &type);

		friend Scene;
		friend class Wal;
	protected:
	public:
		//! @brief A reference to the ECS.
		Scene &_scene;
		//! @brief Get the ID of the entity.
		unsigned getUid() const;
		//! @brief Get the name fo the entity
		std::string getName() const;

		//! @brief Used if the entity is disabled
		bool isDisable() const;
		//! @brief Disable this entity.
		void setDisable(bool disabled);

		//! @brief Has this entity been scheduled for deletion?
		bool shouldDelete() const;
		//! @brief Schedule this entity for deletion
		void scheduleDeletion();

		//! @brief Get a component of a specific type
		//! @tparam The type of the component
		//! @throw NotFoundError if the component could not be found
		//! @return The component of the requested type.
		template<typename T>
		T &getComponent()
		{
			T *ret = this->tryGetComponent<T>();
			if (ret == nullptr)
				throw NotFoundError("No component could be found with the type \"" + std::string(typeid(T).name()) + "\".");
			return *ret;
		}

		//! @brief Get a component of a specific type or null if not found.
		//! @tparam The type of the component
		//! @return The component or nullptr if not found.
		template<typename T>
		T *tryGetComponent()
		{
			const std::type_index &type = typeid(T);
			auto existing = this->_components.find(type);
			if (existing == this->_components.end())
				return nullptr;
			return static_cast<T *>(existing->second.get());
		}

		//! @brief Get a component of a specific type
		//! @tparam The type of the component
		//! @throw NotFoundError if the component could not be found
		//! @return The component of the requested type.
		template<typename T>
		const T &getComponent() const
		{
			const T *ret = this->tryGetComponent<T>();
			if (ret == nullptr)
				throw NotFoundError("No component could be found with the type \"" + std::string(typeid(T).name()) + "\".");
			return *ret;
		}

		//! @brief Get a component of a specific type or null if not found.
		//! @tparam The type of the component
		//! @return The component or nullptr if not found.
		template<typename T>
		const T *tryGetComponent() const
		{
			const std::type_index &type = typeid(T);
			auto existing = this->_components.find(type);
			if (existing == this->_components.end())
				return nullptr;
			return static_cast<T *>(existing->second.get());
		}

		//! @brief Check if this entity has a component.
		//! @param skipDisabled True if you want to skip disabled components (consider them non present), false otherwise.
		//! @tparam T The type of the component
		template<typename T>
		bool hasComponent(bool skipDisabled = true) const
		{
			const std::type_info &type = typeid(T);
			return this->hasComponent(type, skipDisabled);
		}

		//! @brief Check if this entity has a component.
		//! @param skipDisabled True if you want to skip disabled components (consider them non present), false otherwise.
		//! @param type The type of the component
		bool hasComponent(const std::type_info &type, bool skipDisabled = true) const;

		//! @brief Check if this entity has a component.
		//! @param skipDisabled True if you want to skip disabled components (consider them non present), false otherwise.
		//! @param type The type of the component
		bool hasComponent(const std::type_index &type, bool skipDisabled = true) const;

		//! @brief Add a component to this entity. The component is constructed in place.
		//! @throw DuplicateError is thrown if a component with the same type already exist.
		//! @return This entity is returned
		template<typename T, typename ...TNested, typename ...Types>
		Entity &addComponent(Types &&...params)
		{
			const std::type_index &type = typeid(T);
			if (this->hasComponent(type))
				throw DuplicateError("A component of the type \"" + std::string(type.name()) + "\" already exists.");
			this->_components[type] = std::make_unique<T>(*this, TypeHolder<TNested>()..., std::forward<Types>(params)...);
			if (this->_notifyScene)
				this->_componentAdded(type);
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
			if (this->_notifyScene)
				this->_componentRemoved(type);
			return *this;
		}

		//! @brief A default constructor
		explicit Entity(Scene &wal, std::string name, bool notifyScene = true);
		//! @brief An entity is copyable
		Entity(const Entity &);
		//! @brief An entity is movable.
		Entity(Entity &&) = default;
		//! @brief A default destructor
		~Entity() = default;
		//! @brief An entity is not assignable
		Entity &operator=(const Entity &) = delete;

		//! @return true if the two entities hold the same uid
		bool operator==(const Entity &) const;
	};
} // namespace WAL