//
// Created by Zoe Roux on 2021-05-14.
//

#include <chrono>
#include "Wal.hpp"

namespace WAL
{

	SceneManager &WAL::getSceneManger()
	{
		return this->_scenes;
	}

	void WAL::run()
	{
		auto lastTick = std::chrono::steady_clock::now();

		while (!this->_shouldClose) {
			auto now = std::chrono::steady_clock::now();
			auto dtime = now - lastTick;
			lastTick = now;
			// see https://gist.github.com/mariobadr/673bbd5545242fcf9482
		}
	}
}