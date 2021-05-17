//
// Created by Zoe Roux on 2021-05-14.
//

#include <chrono>
#include "Wal.hpp"

using namespace std::chrono_literals;

namespace WAL
{
	std::chrono::nanoseconds WAL::_timestep = 8ms;

	SceneManager &WAL::getSceneManger()
	{
		return this->_scenes;
	}

	void WAL::run()
	{
		auto lastTick = std::chrono::steady_clock::now();
		std::chrono::nanoseconds dtime(0);

		while (!this->_shouldClose) {
			auto now = std::chrono::steady_clock::now();
			dtime += now - lastTick;
			lastTick = now;

			this->_update(dtime);
			while (dtime > WAL::_timestep) {
				dtime -= WAL::_timestep;
				this->_fixedUpdate();
			}
			this->_renderer->render();
		}
	}

	void WAL::_update(std::chrono::nanoseconds dtime)
	{
		auto &entities = this->_scenes.getCurrent().getEntities();

		for (auto &system : this->_systems) {
			for (auto &entity : entities) {
				auto &cmp = system->getComponent();
				if (!entity.hasComponent(cmp))
					continue;
				// TODO handle dependencies.
				system->onUpdate(entity, dtime);
			}
		}
	}

	void WAL::_fixedUpdate()
	{
		auto &entities = this->_scenes.getCurrent().getEntities();

		for (auto &system : this->_systems) {
			for (auto &entity : entities) {
				auto &cmp = system->getComponent();
				if (!entity.hasComponent(cmp))
					continue;
				// TODO handle dependencies.
				system->onFixedUpdate(entity);
			}
		}
	}
}