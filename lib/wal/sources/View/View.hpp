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
	template<typename ...Components>
	class ViewEntity
	{
	private:
		std::tuple<std::reference_wrapper<Entity>, std::reference_wrapper<Components>...> _value;
	public:
		explicit ViewEntity(std::tuple<std::reference_wrapper<Entity>, std::reference_wrapper<Components>...> value)
			: _value(value)
		{}

		Entity *operator->()
		{
			return &(std::get<0>(this->_value).get());
		}

		Entity &operator*()
		{
			return std::get<0>(this->_value);
		}

		operator Entity &()
		{
			return std::get<0>(this->_value);
		}

		template<typename T>
		T &get()
		{
			return std::get<std::reference_wrapper<T>>(this->_value);
		}
	};

	template<typename It, typename ...Components>
	class ViewIterator
	{
	private:
		It _it;

	public:
		ViewEntity<Components...> operator*()
		{
			ViewEntity<Components...> entity(*this->_it);
			return entity;
		}

		ViewEntity<Components...> operator->()
		{
			ViewEntity<Components...> entity(*this->_it);
			return entity;
		}

		ViewIterator &operator++()
		{
			this->_it++;
			return *this;
		}

		ViewIterator operator++(int)
		{
			ViewIterator copy = *this;
			this->_it++;
			return *this;
		}

		bool operator==(const ViewIterator &other) const
		{
			return this->_it == other._it;
		}

		bool operator!=(const ViewIterator &other) const
		{
			return !this->operator==(other);
		}

		explicit ViewIterator(It current)
			: _it(current)
		{}
	};

	//! @brief A basic view used to manipulate view without knowing their type at compile time.
	class IView
	{
	public:
		//! @brief The list of types that every entity of the view has.
		virtual const std::vector<std::type_index> &getTypes() const = 0;

		virtual void emplace_back(Entity &) = 0;

		virtual void erase(const Entity &) = 0;

		//! @brief A default destructor
		virtual ~IView() = default;
	};

	//! @brief A view allowing one to easily access entities containing a set list of component.
	//!        A view is always updated and only references to entities are kept.
	template<typename ...Components>
	class View : public IView
	{
	private:
		using entity_type = std::tuple<std::reference_wrapper<Entity>, std::reference_wrapper<Components>...>;

		//! @brief The list of entities in the view.
		std::vector<entity_type> _entities = {};
		//! @brief The list of types that every entity of the view has.
		std::vector<std::type_index> _types = {};
	public:
		using iterator = ViewIterator<typename std::vector<entity_type>::iterator, Components...>;

		iterator begin()
		{
			return iterator(this->_entities.begin());
		}

		iterator end()
		{
			return iterator(this->_entities.begin());
		}

		const std::vector<std::type_index> &getTypes() const override
		{
			return this->_types;
		}

		void emplace_back(Entity &) override
		{

		}

		void erase(const Entity &) override
		{

		}

		//! @brief Construct a view from a list of entities.
		//!        Those entities are never copied but references to them are kept internally.
		explicit View(std::list<Entity> &scene)
		{
			this->_types = {typeid(Components)...};
			for (auto &entity : scene) {
				auto tuple = std::make_tuple<Components *...>(entity.tryGetComponent<Components>()...);
				if (std::apply([](const auto *...component) {return ((component == nullptr) || ...);}, tuple))
					continue;
				std::apply([&](auto *...component) {
					this->_entities.emplace_back(entity, *component...);
				}, tuple);
			}
		}

		//! @brief Copying a view is not possible since a view must be managed by a scene.
		View(const View &) = delete;
		//! @brief A default destructor
		~View() override = default;
		//! @brief A view is not assignable.
		View &operator=(const View &) = delete;
	};
}