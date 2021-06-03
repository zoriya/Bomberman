//
// Created by Zoe Roux on 2021-05-14.
//


#pragma once

#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
#include "Exception/WalError.hpp"
#include "System/ISystem.hpp"
#include "Models/Callback.hpp"
#include "Scene/Scene.hpp"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

namespace WAL
{
	class Entity;
	class Scene;

	template<typename ...Dependencies>
	class System;

	//! @brief The main WAL class, it is used to setup and run the ECS.
	class Wal
	{
	private:
		//! @brief The list of registered systems
		std::vector<std::unique_ptr<ISystem>> _systems = {};
	public:
		//! @brief The scene that contains entities.
		std::shared_ptr<Scene> scene;
		//! @brief True if the engine should close after the end of the current tick.
		bool shouldClose = false;
		//! @brief The time between each fixed update.
		static constexpr std::chrono::nanoseconds timestep = std::chrono::milliseconds(8);

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
			this->_systems.push_back(std::make_unique<T>(*this, std::forward<Types>(params)...));
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

			#if defined(PLATFORM_WEB)
			std::tuple iterationParams(this, &update, &state);
			return emscripten_set_main_loop_arg((em_arg_callback_func)runIteration<T>, (void *)&iterationParams, 0, 1);
			#else
			return this->run(update, state);
			#endif
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
					for (auto &system : this->_systems) {
						for (auto &entity : system->getView().entities)
							system->onFixedUpdate(entity);
					}
				}
				for (auto &system : this->_systems) {
					for (auto &entity : system->getView().entities)
						system->onUpdate(entity, dtime);
					system->onSelfUpdate();
				}
				callback(*this, state);
			}
		}

		#if defined(PLATFORM_WEB)
		template<typename T>
		static void runIteration(void *param)
		{
			static auto iterationParams = reinterpret_cast<std::tuple<Wal *, Callback<Wal &, T &> *, T *> *>(param);
			static const Callback<Wal &, T &> callback = *((Callback<Wal &, T &> *)std::get<1>(*iterationParams));
			static T *state = (T *)std::get<2>(*iterationParams);
			static Wal *wal = (Wal *)std::get<0>(*iterationParams);
			static auto lastTick = std::chrono::steady_clock::now();
			static std::chrono::nanoseconds fBehind(0);

			auto now = std::chrono::steady_clock::now();
			std::chrono::nanoseconds dtime = now - lastTick;
			fBehind += dtime;
			lastTick = now;
			while (fBehind > Wal::timestep) {
				fBehind -= Wal::timestep;
				wal->_fixedUpdate();
			}
			wal->_update(dtime);
			callback(*wal, *state);
		}
		#endif

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