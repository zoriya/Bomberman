//
// Created by Zoe Roux on 2021-06-03.
//


#pragma once

#include <list>
#include <tuple>
#include <typeindex>
#include <functional>
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief A basic view used to manipulate view without knowing their type at compile time.
	class BaseView
	{
	public:
		//! @brief The list of entities in the view.
		std::vector<std::reference_wrapper<Entity>> entities = {};

		//! @brief The list of types that every entity of the view has.
		std::vector<std::type_index> types = {};

		size_t size() const
		{
			return entities.size();
		}

		//! @brief A default destructor
		~BaseView() = default;
	protected:
		//! @brief A basic view can't be constructed, you should use the View templated class.
		BaseView() = default;
		//! @brief A basic view can't be constructed, you should use the View templated class.
		BaseView(const BaseView &) = default;
		//! @brief A basic view can't be assigned. See the View template class.
		BaseView &operator=(const BaseView &) = default;
	};

	//! @brief A view allowing one to easily access entities containing a set list of component.
	//!        A view is always updated and only references to entities are kept.
	template<typename ...Components>
	class View : public BaseView
	{
	public:
		//! @brief Construct a view from a list of entities.
		//!        Those entities are never copied but references to them are kept internally.
		explicit View(std::list<Entity> &scene)
		{
			this->types = {typeid(Components)...};
			std::copy_if(scene.begin(), scene.end(), std::back_inserter(this->entities), [](Entity &entity) {
				return (entity.hasComponent<Components>() && ...);
			});
		}

		//! @brief Copying a view is not possible since a view must be managed by a scene.
		View(const View &) = delete;
		//! @brief A default destructor
		~View() = default;
		//! @brief A view is not assignable.
		View &operator=(const View &) = delete;
	};
}