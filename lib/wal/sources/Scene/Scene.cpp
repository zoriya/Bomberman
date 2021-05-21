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

	void Scene::removeAll(std::function<bool (const Entity &)> &predicate)
	{
//		this->_entities.erase(std::remove_if(this->_entities.begin(), this->_entities.end(), predicate), this->_entities.end());
	}
}

