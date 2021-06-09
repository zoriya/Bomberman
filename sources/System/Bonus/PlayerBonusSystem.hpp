//
// Created by hbenjamin on 09/06/2021.
//

#pragma once

#include <System/System.hpp>
#include <Wal.hpp>
#include "Models/Vector3.hpp"
#include "Component/Bonus/PlayerBonusComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/BombHolder/BombHolderComponent.hpp"

namespace BBM
{
	//! @brief The system that allow one to place bombs.
	class PlayerBonusSystem : public WAL::System<PlayerBonusComponent, ControllableComponent, BombHolderComponent>
	{
	private:
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<PlayerBonusComponent, ControllableComponent, BombHolderComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @brief A default constructor
		explicit PlayerBonusSystem(WAL::Wal &wal);
		//! @brief A bomb holder system is copy constructable
		PlayerBonusSystem(const PlayerBonusSystem &) = default;
		//! @brief A default destructor
		~PlayerBonusSystem() override = default;
		//! @brief A bomb holder system is not assignable.
		PlayerBonusSystem &operator=(const PlayerBonusSystem &) = delete;
	};
}

