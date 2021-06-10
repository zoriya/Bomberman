#pragma once

#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Health entities.
	class LobbySystem : public WAL::System<>
	{
	public:
		//! @inherit
		void onSelfUpdate() override;

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