//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <vector>
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief Represent a single scene that contains entities.
	class Scene
	{
	private:
		//! @brief The list of registered entities
		std::vector<Entity> _entity;
	public:
		//! @brief Get the list of entities.
		std::vector<Entity> &getEntities();
	};
}
