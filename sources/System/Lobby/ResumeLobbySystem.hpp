//
// Created by hbenjamin on 6/18/21.
//

#pragma once

#include "System/System.hpp"
#include "Component/Lobby/ResumeLobbyComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"
#include <array>
#include <string>

namespace BBM
{
	//! @brief A system to handle Health entities.
	class ResumeLobbySystem : public WAL::System<ResumeLobbyComponent, Drawable2DComponent>
	{
	public:

		//! @brief Add a controller for the player when we resume a game
		static void resumeToGame(WAL::Wal &wal);

		//! @inherit
		void onUpdate(WAL::ViewEntity<ResumeLobbyComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @inherit
		void onSelfUpdate(std::chrono::nanoseconds dtime) override;

		//! @brief Check if every player is ready.
		//! @param scene The lobby scene containing lobby players.
		static bool playersAreReady(WAL::Scene &scene);

		//! @brief Reset the resume lobby scene to it's default state.
		void unloadLobbyFromResume();

		//! @brief A default constructor
		explicit ResumeLobbySystem(WAL::Wal &wal);
		//! @brief A Lobby system is copy constructable
		ResumeLobbySystem(const ResumeLobbySystem &) = default;
		//! @brief A default destructor
		~ResumeLobbySystem() override = default;
		//! @brief A system is not assignable.
		ResumeLobbySystem &operator=(const ResumeLobbySystem &) = delete;
	};
}