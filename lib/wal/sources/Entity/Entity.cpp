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

	Entity::Entity(Scene &scene, std::string name, bool notifyScene)
		: _uid(Entity::nextID++),
		_scene(scene),
		_name(std::move(name)),
		_notifyScene(notifyScene)
	{ }

	Entity::Entity(const Entity &other)
		: _uid(Entity::nextID++),
		_scene(other._scene),
		_name(other._name),
		_disabled(other._disabled),
		_notifyScene(other._notifyScene)
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
		if (this->hasComponent(type, false))
			throw DuplicateError("A component of the type \"" + std::string(type.name()) + "\" already exists.");
		this->_components.emplace(type, component.clone(*this));
		if (this->_notifyScene)
			this->_scene._componentAdded(*this, type);
		return *this;
	}

	bool Entity::hasComponent(const std::type_info &type, bool skipDisabled) const
	{
		return this->hasComponent(static_cast<const std::type_index &>(type), skipDisabled);
	}

	bool Entity::hasComponent(const std::type_index &type, bool skipDisabled) const
	{
		auto cmp = this->_components.find(type);
		if (cmp == this->_components.end())
			return false;
		if (skipDisabled)
			return !cmp->second->isDisabled();
		return true;
	}

	void Entity::_componentAdded(const std::type_index &type)
	{
		this->_scene._componentAdded(*this, type);
	}

	void Entity::_componentRemoved(const std::type_index &type)
	{
		this->_scene._componentRemoved(*this, type);
	}

	bool Entity::operator==(const Entity &other) const
	{
		return other.getUid() == this->_uid;
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