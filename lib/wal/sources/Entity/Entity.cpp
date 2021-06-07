//
// Created by Zoe Roux on 2021-05-14.
//

#include "Entity/Entity.hpp"
#include "Scene/Scene.hpp"
#include <string>
#include <utility>

namespace WAL
{
	unsigned Entity::nextID = 0;

	Entity::Entity(Scene &scene, std::string name)
		: _uid(Entity::nextID++),
		_scene(scene),
		_name(std::move(name))
	{ }

	Entity::Entity(const Entity &other)
		: _uid(Entity::nextID++),
		_scene(other._scene),
		_name(other._name),
		_disabled(other._disabled)
	{
		for (const auto &cmp : other._components)
			this->addComponent(*cmp.second);
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
		const std::type_index &type = typeid(component);
		if (this->hasComponent(type))
			throw DuplicateError("A component of the type \"" + std::string(type.name()) + "\" already exists.");
		this->_components.emplace(type, component.clone(*this));
		this->_scene._componentAdded(*this, type);
		return *this;
	}

	bool Entity::hasComponent(const std::type_info &type) const
	{
		return this->hasComponent(static_cast<const std::type_index &>(type));
	}

	bool Entity::hasComponent(const std::type_index &type) const
	{
		return this->_components.contains(type);
	}

	void Entity::_componentAdded(const std::type_index &type)
	{
		this->_scene._componentAdded(*this, type);
	}

	void Entity::_componentRemoved(const std::type_index &type)
	{
		this->_scene._componentRemoved(*this, type);
	}
} // namespace WAL