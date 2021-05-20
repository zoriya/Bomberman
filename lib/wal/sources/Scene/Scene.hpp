//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <vector>
#include <functional>
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief Represent a single scene that contains entities.
	class Scene
	{
	private:
		//! @brief The list of registered entities
		std::vector<Entity> _entities = {};
	public:
		//! @brief Get the list of entities.
		std::vector<Entity> &getEntities();

		//! @brief Add a new entity to the scene, you can use this method with the same arguments as the entity's constructor.
		//! @return The current scene is returned to allow you to chain call.
		template <class ...Params>
		Scene &addEntity(Params ...params)
		{
			this->_entities.emplace_back(params...);
			return *this;
		}

		//! @brief Remove every entity of this scene that matches the given predicate
		//! @param predicate The predicate used to filer entities
		void removeAll(std::function<bool (const Entity &)> &predicate);

		//! @brief A default constructor
		Scene() = default;
		//! @brief A scene is copy constructable
		Scene(const Scene &) = default;
		//! @brief A default destructor
		~Scene() = default;
		//! @brief A scene is assignable
		Scene &operator=(const Scene &) = default;
	};
}
