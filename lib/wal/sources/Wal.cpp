//
// Created by Zoe Roux on 2021-05-14.
//

#include <chrono>
#include <algorithm>
#include "Wal.hpp"

using namespace std::chrono_literals;

namespace WAL
{
	std::chrono::nanoseconds Wal::timestep = 8ms;

	void Wal::_update(std::chrono::nanoseconds dtime)
	{
		auto &entities = this->_scene.getEntities();

		for (auto &system : this->_systems) {
			for (auto &entity : entities) {
				if (!Wal::_hasDependencies(entity, *system))
					continue;
				system->onUpdate(entity, dtime);
			}
			system->onSelfUpdate();
		}
	}

	void Wal::_fixedUpdate()
	{
		auto &entities = this->_scene.getEntities();

		for (auto &system : this->_systems) {
			for (auto &entity : entities) {
				if (!Wal::_hasDependencies(entity, *system))
					continue;
				system->onFixedUpdate(entity);
			}
		}
	}

	bool Wal::_hasDependencies(const Entity &entity, const System &system)
	{
		// TODO use an hashmap to cache results.
		const auto &dependency = system.getDependencies();
		return std::ranges::all_of(dependency.begin(), dependency.end(), [&entity](const auto &dependency) {
			return entity.hasComponent(dependency);
		});
	}
}