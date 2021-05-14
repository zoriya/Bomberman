//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <vector>
#include <memory>
#include <typeinfo>
#include <Exception/WalError.hpp>
#include "Events/EventManager.hpp"
#include "Renderer/Renderer.hpp"
#include "Scene/SceneManager.hpp"
#include "Entity/Entity.hpp"
#include "System/System.hpp"

namespace WAL
{
	//! @brief The main WAL class, it is used to setup and run the ECS.
	class WAL
	{
	private:
		//! @brief The scene manager that allow multiple scene to work together.
		SceneManager _scenes;
		//! @brief The event manager
		EventManager _eventManager;
		//! @brief The list of registered systems
		std::vector<std::unique_ptr<System>> _systems = {};
		//! @brief The renderer used to draw entities
		std::unique_ptr<Renderer> _renderer;
	public:
		//! @brief Create a new system in place.
		//! @return The wal instance used to call this function is returned. This allow method chaining.
		template<typename T, class ...Types>
		WAL &addSystem(Types ...params)
		{
			const std::type_info &type = typeid(T);
			auto &existing =std::find(this->_systems.begin(), this->_systems.end(), [&type] (auto &sys) {
				return typeid(sys) == type;
			});
			if (existing != this->_systems.end())
				throw SystemExistError("A system of the type \"" + std::string(type.name()) + "\" already exists.");
			this->_systems.push_back(std::make_unique(params...));
			return *this;
		}

		//! @brief Add a system by copy.
		//! @return The wal instance used to call this function is returned. This allow method chaining.
		template<typename T>
		WAL &addSystem(const T &system)
		{
			const std::type_info &type = typeid(T);
			auto &existing =std::find(this->_systems.begin(), this->_systems.end(), [&type] (auto &sys) {
				return typeid(sys) == type;
			});
			if (existing != this->_systems.end())
				throw SystemExistError("A system of the type \"" + std::string(type.name()) + "\" already exists.");
			this->_systems.push_back(std::make_unique(system));
			return *this;
		}

		//! @brief Remove a system using it's type.
		template<typename T>
		WAL &removeSystem()
		{
			const std::type_info &type = typeid(T);
			auto &existing =std::find(this->_systems.begin(), this->_systems.end(), [&type] (auto &sys) {
				return typeid(sys) == type;
			});
			if (existing == this->_systems.end())
				throw NotFoundError("No system could be found with the type \"" + std::string(type.name()) + "\".");
			return *this;
		}

		//! @brief Get the scene manager.
		SceneManager &getSceneManger();

		//! @brief Start the game loop
		void run();

		//! @brief A default constructor
		WAL() = default;
		//! @brief A WAL can't be copy constructed
		WAL(const WAL &) = delete;
		//! @brief A default destructor
		~WAL() = default;
		//! @brief A default assignment operator
		WAL &operator=(const WAL &) = default;
	};
}
