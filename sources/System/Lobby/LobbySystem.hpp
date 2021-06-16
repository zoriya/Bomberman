//
// Created by Zoe Roux on 6/11/21.
//

#pragma once

#include "System/System.hpp"
#include "Component/Lobby/LobbyComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include <array>
#include <string>

namespace BBM
{
	//! @brief A system to handle Health entities.
	class LobbySystem : public WAL::System<LobbyComponent, Drawable2DComponent>
	{
	private:

		void _nextColor(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity);

		static std::array<std::string, 4> _colors;

		static std::array<RAY::Color, 4> _rayColors;

		std::array<bool, 4> _colorTaken = {};
	public:
		//! @brief Add a controller for the player.
		static void addController(WAL::Entity &player, ControllableComponent::Layout layout);

		//! @brief Add a controller for the player when we resume a game
		static void resumeToGame(WAL::Wal &wal);

		//! @inherit
		void onUpdate(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @inherit
		void onSelfUpdate() override;

		//! @brief Check if every player is ready.
		//! @param scene The lobby scene containing lobby players.
		static bool playersAreReady(WAL::Scene &scene);

		//! @brief Inform the engine that the next scene should be the game scene and load it.
		//! @param wal The engine.
		static void switchToGame(WAL::Wal &wal);

		//! @brief A default constructor
		explicit LobbySystem(WAL::Wal &wal);
		//! @brief A Lobby system is copy constructable
		LobbySystem(const LobbySystem &) = default;
		//! @brief A default destructor
		~LobbySystem() override = default;
		//! @brief A system is not assignable.
		LobbySystem &operator=(const LobbySystem &) = delete;
	};
}