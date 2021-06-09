//
// Created by Tom Augier on 05/06/2021
//

#pragma once

#include "System/System.hpp"
#include "Window.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Component/Health/HealthComponent.hpp"
#include <Component/Controllable/ControllableComponent.hpp>
#include "Wal.hpp"

namespace BBM
{
	class PlayerSoundManagerSystem : public WAL::System<SoundComponent, ControllableComponent, HealthComponent>
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<SoundComponent, ControllableComponent, HealthComponent> &entity) override;
		
		//! @brief ctor
		PlayerSoundManagerSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		PlayerSoundManagerSystem(const PlayerSoundManagerSystem &) = default;
		//! @brief Default dtor
		~PlayerSoundManagerSystem() override = default;
		//! @brief A SoundManager screen system can't be assigned.
		PlayerSoundManagerSystem &operator=(const PlayerSoundManagerSystem &) = delete;
	};
}
