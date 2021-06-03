//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <vector>
#include <functional>
#include <View/BaseView.hpp>
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief Represent a single scene that contains entities.
	class Scene
	{
	private:
		//! @brief The list of registered entities
		std::vector<Entity> _entities = {};
		//! @brief The list of cached views to update.
		std::vector<std::shared_ptr<BaseView>> _views = {};

		//! @brief Notify this scene that a component has been added to the given entity.
		//! @param entity The entity with the new component
		//! @param type The type of the component added.
		void _componentAdded(Entity &entity, const std::type_index &type);
		//! @brief Notify this scene that a component has been removed to the given entity.
		//! @param entity The entity with the removed component
		//! @param type The type of the component removed.
		void _componentRemoved(const Entity &entity, const std::type_index &type);
	public:
		//! @brief Get the list of entities.
		std::vector<Entity> &getEntities();

		//! @brief Add a new entity to the scene.
		//! @param name The name of the created entity.
		//! @return The created entity is returned.
		Entity &addEntity(const std::string &name);

		template<typename ...Components>
		View<Components...> &view()
		{
			static auto view = std::make_shared<View<Components...>>(this->_entities);
			this->_views.emplace_back(view);
			return *view;
		}

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