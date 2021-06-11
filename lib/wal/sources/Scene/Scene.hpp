//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <vector>
#include <list>
#include <functional>
#include <View/View.hpp>
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief Represent a single scene that contains entities.
	class Scene
	{
	private:
		static int _nextID;
		//! @brief An ID representing this scene.
		int _id = _nextID++;

		//! @brief The list of registered entities
		std::list<Entity> _entities = {};
		//! @brief The list of entities to add on the next call to applyChanges.
		std::list<Entity> _newEntities = {};
		//! @brief The list of cached views to update.
		std::vector<std::shared_ptr<IView>> _views = {};

		//! @brief Notify this scene that a component has been added to the given entity.
		//! @param entity The entity with the new component
		//! @param type The type of the component added.
		void _componentAdded(Entity &entity, const std::type_index &type);
		//! @brief Notify this scene that a component has been removed to the given entity.
		//! @param entity The entity with the removed component
		//! @param type The type of the component removed.
		void _componentRemoved(const Entity &entity, const std::type_index &type);
		//! @brief Remove an entity from every views.
		//! @param entity The entity to remove.
		void _entityRemoved(const Entity &entity);
	public:
		//! @brief Get the ID of this scene.
		int getID() const;

		//! @brief Get the list of entities.
		std::list<Entity> &getEntities();

		//! @brief Add a new entity to the scene.
		//! @param name The name of the created entity.
		//! @return The created entity is returned.
		Entity &addEntity(const std::string &name);

		//! @brief Add a new entity to the scene, this entity will be added on the next call to applyChanges.
		//! @param name The name of the created entity.
		//! @return The created entity is returned.
		Entity &scheduleNewEntity(const std::string &name);

		template<typename ...Components>
		View<Components...> &view()
		{
			static std::unordered_map<int, std::weak_ptr<View<Components...>>> cache;
			auto existing = cache.find(this->_id);
			if (existing != cache.end() && !existing->second.expired())
				return *existing->second.lock();
			auto view = std::make_shared<View<Components...>>(this->_entities);
			this->_views.emplace_back(view);
			cache.emplace(this->_id, view);
			return *view;
		}

		//! @brief Delete entities marked as deleted and create scheduled entities.
		void applyChanges();

		//! @brief A default constructor
		Scene() = default;
		//! @brief A scene is copy constructable
		Scene(const Scene &) = default;
		//! @brief A default destructor
		~Scene() = default;
		//! @brief A scene is assignable
		Scene &operator=(const Scene &);
		Scene(Scene &&) = default;

		friend Entity;
	};
} // namespace WAL