//
// Created by Zoe Roux on 2021-05-14.
//

#include "Entity/Entity.hpp"
#include <string>
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
		if (this->hasComponent(typeid(component), false))
			throw DuplicateError("A component of the type \"" + std::string(typeid(component).name()) + "\" already exists.");
		this->_components.emplace_back(component.clone(*this));
		return *this;
	}

	bool Entity::hasComponent(const std::type_info &type, bool skipDisabled) const
	{
		auto existing = std::find_if(this->_components.begin(), this->_components.end(), [&type] (const auto &cmp) {
			return typeid(*cmp) == type;
		});
		if (existing == this->_components.end())
			return false;
		if (skipDisabled)
			return !(*existing)->isDisabled();
		return true;
	}

	bool Entity::hasComponent(const std::type_index &type, bool skipDisabled) const
	{
		auto existing = std::find_if(this->_components.begin(), this->_components.end(), [&type] (const auto &cmp) {
			return std::type_index(typeid(*cmp)) == type;
		});
		if (existing == this->_components.end())
			return false;
		if (skipDisabled)
			return !(*existing)->isDisabled();
		return true;
	}

	bool Entity::shouldDelete() const
	{
		return this->_shouldDelete;
	}

	void Entity::scheduleDeletion()
	{
		this->_shouldDelete = true;
	}
} // namespace WAL