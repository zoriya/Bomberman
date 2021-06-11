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
	class MenuSoundManagerSystem : public WAL::System<SoundComponent, ControllableComponent>
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<SoundComponent, ControllableComponent> &entity) override;
		
		//! @brief ctor
		MenuSoundManagerSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		MenuSoundManagerSystem(const MenuSoundManagerSystem &) = default;
		//! @brief Default dtor
		~MenuSoundManagerSystem() override = default;
		//! @brief A SoundManager screen system can't be assigned.
		MenuSoundManagerSystem &operator=(const MenuSoundManagerSystem &) = delete;
	};
}
