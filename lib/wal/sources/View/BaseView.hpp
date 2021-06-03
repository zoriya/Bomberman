//
// Created by Zoe Roux on 2021-06-03.
//


#pragma once

#include <vector>
#include <tuple>
#include <typeindex>
#include <functional>
#include "Entity/Entity.hpp"

namespace WAL
{
	class BaseView
	{
	public:
		std::vector<std::reference_wrapper<Entity>> entities = {};

		std::vector<std::type_index> types = {};

		size_t size()
		{
			return entities.size();
		}

//		std::vector<std::reference_wrapper<Entity>> &view(const Components &...index) requires(std::is_same_v<Components...>)
//		{
//			static std::vector<std::reference_wrapper<Entity>> view;
//
//			std::copy_if(this->_entities.begin(), this->_entities.end(), std::back_inserter(view), [&index...](Entity &entity) {
//				return (entity.hasComponent(index) && ...);
//			});
//			return view;
//		}
	};

	template<typename ...Components>
	class View : public BaseView
	{
	public:
		explicit View(std::vector<Entity> &scene)
		{
			std::copy_if(scene.begin(), scene.end(), std::back_inserter(this->entities), [](Entity &entity) {
				return (entity.hasComponent<Components>() && ...);
			});
		}
	};
}