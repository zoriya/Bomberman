//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <queue>
#include "Scene/Scene.hpp"

namespace WAL
{
	//! @brief A class to manage scenes
	class SceneManager
	{
	private:
		std::deque<Scene> _scenes = {};
	public:
		//! @brief Add a scene to the container and move to it.
		//! @return The manager instance used to call this function is returned. This allow method chaining.
		SceneManager &addScene(Scene &&scene);

		//! @brief Add a scene before the current scene to allow
		//! @return The manager instance used to call this function is returned. This allow method chaining.
		SceneManager &addBackScene(Scene &&scene);

		//! @breif Get the current scene
		Scene &getCurrent();

		//! @brief Remove the current scene and switch to the previous scene on the stack.
		//! @return The manager instance used to call this function is returned. This allow method chaining.
		SceneManager &closeCurrent();

		//! @brief A default constructor
		SceneManager() = default;
		//! @brief A scene manager is copy constructable
		SceneManager(const SceneManager &) = default;
		//! @brief A default destructor.
		~SceneManager() = default;
		//! @brief A scene manager is assignable
		SceneManager &operator=(const SceneManager &) = default;
	};
}
