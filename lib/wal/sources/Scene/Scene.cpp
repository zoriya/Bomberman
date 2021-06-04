//
// Created by Zoe Roux on 2021-05-14.
//

#include "Scene.hpp"

namespace WAL
{
	int Scene::_nextID = 0;

	std::list<Entity> &Scene::getEntities()
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

	void Scene::_componentAdded(Entity &entity, const std::type_index &type)
	{
		for (auto &view : this->_views) {
			if (std::find(view->getTypes().begin(), view->getTypes().end(), type) == view->getTypes().end())
				continue;
			bool valid = std::all_of(view->getTypes().begin(), view->getTypes().end(), [&entity](const auto &type){
				return entity.hasComponent(type);
			});
			if (valid)
				view->emplace_back(entity);
		}
	}

	void Scene::_componentRemoved(const Entity &entity, const std::type_index &type)
	{
		for (auto &view : this->_views) {
			if (std::find(view->getTypes().begin(), view->getTypes().end(), type) == view->getTypes().end())
				continue;
			view->erase(entity);
		}
	}
} // namespace WAL