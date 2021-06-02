//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <vector>
#include <functional>
#include "View/View.hpp"
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief Represent a single scene that contains entities.
	class Scene
	{
	private:
		//! @brief The list of registered entities
		std::vector<Entity> _entities = {};
		//! @brief A list of cached views.
//		std::vector<View> _views = {};
	public:
		//! @brief Get the list of entities.
		std::vector<Entity> &getEntities();

		//! @brief Add a new entity to the scene, you can use this method with the same arguments as the entity's constructor.
		//! @return The current scene is returned to allow you to chain call.
		template <class ...Params>
		Entity &addEntity(Params &&...params)
		{
			return this->_entities.emplace_back(std::forward<Params>(params)...);
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
	};
} // namespace WAL