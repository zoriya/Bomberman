//
// Created by Zoe Roux on 2021-05-14.
//

#include <chrono>
#include "Wal.hpp"

using namespace std::chrono_literals;

namespace WAL
{
	std::chrono::nanoseconds Wal::timestep = 8ms;

	SceneManager &Wal::getSceneManager()
	{
		return this->_sceneManager;
	}

	void Wal::run()
	{
		auto lastTick = std::chrono::steady_clock::now();
		std::chrono::nanoseconds fBehind(0);

		while (!this->_shouldClose) {
			auto now = std::chrono::steady_clock::now();
			std::chrono::nanoseconds dtime = now - lastTick;
			fBehind += dtime;
			lastTick = now;

			while (fBehind > Wal::timestep) {
				fBehind -= Wal::timestep;
				this->_fixedUpdate();
			}
			this->_update(dtime);
		}
	}

	void Wal::_update(std::chrono::nanoseconds dtime)
	{
		auto &entities = this->_sceneManager.getCurrent().getEntities();

		for (auto &system : this->_systems) {
			for (auto &entity : entities) {
				const auto &cmp = system->getComponent();
				if (!entity.hasComponent(cmp))
					continue;
				// TODO handle dependencies.
				system->onUpdate(entity, dtime);
			}
			system->onSelfUpdate();
		}
	}

	void Wal::_fixedUpdate()
	{
		auto &entities = this->_sceneManager.getCurrent().getEntities();

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