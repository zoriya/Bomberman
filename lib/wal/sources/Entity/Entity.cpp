//
// Created by Zoe Roux on 2021-05-14.
//

#include "Entity/Entity.hpp"

#include <utility>

namespace WAL
{
	unsigned Entity::nextID = 0;

	Entity::Entity(std::string name)
		: _uid(Entity::nextID++),
		_name(std::move(name))
	{ }

	Entity::Entity(const Entity &other)
		: _uid(Entity::nextID++),
		_name(other._name),
		_disabled(other._disabled)
	{
		for (const auto &cmp : other._components)
			this->addComponent(*cmp);
	}

	unsigned Entity::getUid() const
	{
		return this->_uid;
	}

	std::string Entity::getName() const
	{
		return this->_name;
	}

	bool Entity::isDisable() const
	{
		return this->_disabled;
	}

	void Entity::setDisable(bool disabled)
	{
		this->_disabled = disabled;
	}

	Entity &Entity::addComponent(const Component &component)
	{
		// TODO handle duplicates
//		if (this->hasComponent<T>())
//			throw DuplicateError("A component of the type \"" + std::string(typeid(T).name()) + "\" already exists.");
		this->_components.emplace_back(component.clone(*this));
		return *this;
	}
}