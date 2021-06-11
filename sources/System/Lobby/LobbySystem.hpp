#pragma once

#include "System/System.hpp"
#include "Component/Lobby/LobbyComponent.hpp"

namespace BBM
{
	//! @brief A system to handle Health entities.
	class LobbySystem : public WAL::System<LobbyComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<LobbyComponent> &entity, std::chrono::nanoseconds dtime) override;

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