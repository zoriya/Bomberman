//
// Created by Zoe Roux on 2021-05-14.
//

#include "SceneManager.hpp"

namespace WAL
{
	SceneManager &WAL::SceneManager::addScene(WAL::Scene &&scene)
	{
		this->_scenes.push_front(scene);
		return *this;
	}

	SceneManager &SceneManager::addBackScene(Scene &&scene)
	{
		this->_scenes.insert(++this->_scenes.begin(), scene);
		return *this;
	}

	Scene &SceneManager::getCurrent()
	{
		if (this->_scenes.empty())
			throw NotFoundError("No scene exists.");
		return this->_scenes.front();
	}

	SceneManager &SceneManager::closeCurrent()
	{
		this->_scenes.pop_front();
		return *this;
	}
}