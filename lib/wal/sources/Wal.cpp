//
// Created by Zoe Roux on 2021-05-14.
//

#include <chrono>
#include "Wal.hpp"

using namespace std::chrono_literals;

namespace WAL
{
	std::chrono::nanoseconds Wal::timestep = 8ms;

	SceneManager &Wal::getSceneManger()
	{
		return this->_scenes;
	}

	void Wal::run()
	{
		auto lastTick = std::chrono::steady_clock::now();
		std::chrono::nanoseconds dtime(0);

		while (!this->_shouldClose) {
			auto now = std::chrono::steady_clock::now();
			dtime += now - lastTick;
			lastTick = now;

			this->_update(dtime);
			while (dtime > Wal::timestep) {
				dtime -= Wal::timestep;
				this->_fixedUpdate();
			}
			this->_renderer->render();
		}
	}

	void Wal::_update(std::chrono::nanoseconds dtime)
	{
		auto &entities = this->_scenes.getCurrent().getEntities();

		for (auto &system : this->_systems) {
			for (auto &entity : entities) {
				const auto &cmp = system->getComponent();
				if (!entity.hasComponent(cmp))
					continue;
				// TODO handle dependencies.
				system->onUpdate(entity, dtime);
			}
		}
	}

	void Wal::_fixedUpdate()
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