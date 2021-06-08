//
// Created by Zoe Roux on 2021-05-14.
//

#include "Scene.hpp"
#include <algorithm>

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

	Entity &Scene::scheduleNewEntity(const std::string &name)
	{
		return this->_newEntities.emplace_back(*this, name, false);
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

	void Scene::_entityRemoved(const Entity &entity)
	{
		for (auto &view : this->_views)
			view->erase(entity);
	}

	void Scene::applyChanges()
	{
		this->_entities.remove_if([this](auto &entity) {
			if (!entity.shouldDelete())
				return false;
			this->_entityRemoved(entity);
			return true;
		});
		for (auto &entity : this->_newEntities) {
			for (auto &view : this->_views) {
				bool valid = std::all_of(view->getTypes().begin(), view->getTypes().end(), [&entity](const auto &type){
					return entity.hasComponent(type);
				});
				if (valid)
					view->emplace_back(entity);
			}
			entity._notifyScene = true;
		}
		this->_entities.splice(this->_entities.end(), this->_newEntities);
	}
} // namespace WAL