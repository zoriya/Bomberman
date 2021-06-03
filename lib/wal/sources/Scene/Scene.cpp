//
// Created by Zoe Roux on 2021-05-14.
//

#include "Scene.hpp"

namespace WAL
{
	std::vector<Entity> &Scene::getEntities()
	{
		return this->_entities;
	}

	Scene &Scene::operator=(const Scene &)
	{
		return *this;
	}

	Entity &Scene::addEntity(const std::string &name)
	{
		return this->_entities.emplace_back(*this, name);
	}

	void Scene::_componentAdded(const Entity &entity, std::type_index type)
	{

	}

	void Scene::_componentRemoved(const Entity &entity, std::type_index type)
	{

	}
} // namespace WAL