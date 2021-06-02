//
// Created by Zoe Roux on 2021-06-02.
//


#pragma once

#include <vector>
#include <Entity/Entity.hpp>

namespace WAL
{
	//! @brief A view caching entities containing requested components
	template<typename ...Components>
	class View
	{
		//! @brief A list of reference to entities that contains the
		std::vector<std::reference_wrapper<Entity>> entities;

		explicit View(std::vector<Entity> &entities)
			: entities()
		{
			std::copy_if(entities.begin(), entities.end(), std::back_inserter(this->entities), [](Entity &entity) {
				return (entity.hasComponent<Components>() && ...);
			});
		}

		//! @brief A default copy constructor.
		View(const View &) = default;
		//! @brief A default destructor.
		~View() = default;
		//! @brief A View is assignable.
		View &operator=(const View &) = default;
	};
}