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

	void Scene::_componentAdded(Entity &entity, const std::type_index &type)
	{
		for (auto &view : this->_views) {
			if (std::find(view->types.begin(), view->types.end(), type) == view->types.end())
				continue;
			bool valid = std::all_of(view->types.begin(), view->types.end(), [&entity](const auto &type){
				return entity.hasComponent(type);
			});
			if (valid)
				view->entities.emplace_back(entity);
		}
	}

	void Scene::_componentRemoved(const Entity &entity, const std::type_index &type)
	{
		for (auto &view : this->_views) {
			if (std::find(view->types.begin(), view->types.end(), type) == view->types.end())
				continue;
			view->entities.erase(std::remove_if(view->entities.begin(), view->entities.end(), [&entity](const auto &ref)
			{
				return &ref.get() == &entity;
			}), view->entities.end());
		}
	}
} // namespace WAL