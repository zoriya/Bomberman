//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
#include "Exception/WalError.hpp"
#include "Scene/Scene.hpp"
#include "Entity/Entity.hpp"
#include "System/System.hpp"
#include "Models/Callback.hpp"

namespace WAL
{
	//! @brief The main WAL class, it is used to setup and run the ECS.
	class Wal
	{
	private:
		//! @brief The list of registered systems
		std::vector<std::unique_ptr<System>> _systems = {};

		//! @brief Call the onUpdate of every system with every component
		void _update(std::chrono::nanoseconds dtime);

		//! @brief Call the onFixedUpdate of every system with every component
		void _fixedUpdate();

		//! @brief Check if an entity met a system's dependencies.
		//! @param entity The entity to check
		//! @param system The system that will list dependencies
		//! @return True if all dependencies are met, false otherwise.
		static bool _hasDependencies(const Entity &entity, const System &system);
	public:
		//! @brief The scene that contains entities.
		std::shared_ptr<Scene> scene;
		//! @brief True if the engine should close after the end of the current tick.
		bool shouldClose = false;
		//! @brief The time between each fixed update.
		static std::chrono::nanoseconds timestep;

		//! @brief Create a new system in place.
		//! @return The wal instance used to call this function is returned. This allow method chaining.
		template<typename T, class ...Types>
		Wal &addSystem(Types &&...params)
		{
			const std::type_info &type = typeid(T);
			auto existing = std::find_if(this->_systems.begin(), this->_systems.end(), [&type] (auto &sys) {
				return typeid(*sys) == type;
			});
			if (existing != this->_systems.end())
				throw DuplicateError("A system of the type \"" + std::string(type.name()) + "\" already exists.");
			this->_systems.push_back(std::make_unique<T>(std::forward<Types>(params)...));
			return *this;
		}

		//! @brief Add a system by copy.
		//! @return The wal instance used to call this function is returned. This allow method chaining.
		template<typename T>
		Wal &addSystem(const T &system)
		{
			const std::type_info &type = typeid(T);
			auto existing = std::find_if(this->_systems.begin(), this->_systems.end(), [&type] (auto &sys) {
				return typeid(*sys) == type;
			});
			if (existing != this->_systems.end())
				throw DuplicateError("A system of the type \"" + std::string(type.name()) + "\" already exists.");
			this->_systems.push_back(std::make_unique<T>(system));
			return *this;
		}

		//! @brief Get a system of a specific type
		//! @tparam T the type of the system.
		template<typename T>
		T &getSystem()
		{
			const std::type_info &type = typeid(T);
			auto existing = std::find_if(this->_systems.begin(), this->_systems.end(), [&type] (auto &sys) {
				return typeid(*sys) == type;
			});
			if (existing == this->_systems.end())
				throw NotFoundError("A system of the type \"" + std::string(type.name()) + "\" could not be found.");
			return *static_cast<T *>(existing->get());
		}

		//! @brief Remove a system using it's type.
		template<typename T>
		Wal &removeSystem()
		{
			const std::type_info &type = typeid(T);
			auto existing = std::find_if(this->_systems.begin(), this->_systems.end(), [&type] (auto &sys) {
				return typeid(*sys) == type;
			});
			if (existing == this->_systems.end())
				throw NotFoundError("No system could be found with the type \"" + std::string(type.name()) + "\".");
			this->_systems.erase(existing);
			return *this;
		}

		//! @brief Start the game loop
		//! @param callback A callback called after each update of the game. It allow you to update the engine based on a specific game state. (you can also update the game state here)
		//! @param state An initial game state. If not specified, it will be defaulted.
		//! @tparam T A type used to track your game state. It must be default constructable.
		template<typename T>
		void run(const std::function<void (Wal &, T &)> &callback, T state = T())
		{
			Callback<Wal &, T &> update(callback);
			return this->run(update, state);
		}

		//! @brief Start the game loop
		//! @param callback A callback called after each update of the game. It allow you to update the engine based on a specific game state. (you can also update the game state here)
		//! @param state An initial game state. If not specified, it will be defaulted.
		//! @tparam T A type used to track your game state. It must be default constructable.
		template<typename T>
		void run(const Callback<Wal &, T &> &callback, T state = T())
		{
			auto lastTick = std::chrono::steady_clock::now();
			std::chrono::nanoseconds fBehind(0);

			while (!this->shouldClose) {
				auto now = std::chrono::steady_clock::now();
				std::chrono::nanoseconds dtime = now - lastTick;
				fBehind += dtime;
				lastTick = now;

				while (fBehind > Wal::timestep) {
					fBehind -= Wal::timestep;
					this->_fixedUpdate();
				}
				this->_update(dtime);
				// TODO delete entities scheduled for deletion.
				callback(*this, state);
			}
		}

		//! @brief A default constructor
		Wal() = default;
		//! @brief A WAL can't be copy constructed
		Wal(const Wal &) = delete;
		//! @brief A default destructor
		~Wal() = default;
		//! @brief A WAL can't be assigned.
		Wal &operator=(const Wal &) = delete;
	};
} // namespace WAL