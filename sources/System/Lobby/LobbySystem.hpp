//
// Created by Zoe Roux on 6/11/21.
//

#pragma once

#include "System/System.hpp"
#include "Component/Lobby/LobbyComponent.hpp"

namespace BBM
{
	//! @brief A system to handle Health entities.
	class LobbySystem : public WAL::System<LobbyComponent, Drawable2DComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @inherit
		void onSelfUpdate() override;

		//! @brief Check if every player is ready.
		//! @param scene The lobby scene containing lobby players.
		static bool playersAreReady(WAL::Scene &scene);

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