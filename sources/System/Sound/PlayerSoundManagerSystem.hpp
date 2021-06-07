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
	class SoundManagerSystem : public WAL::System
	{
	public:
        //! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;
		
		//! @brief ctor
		SoundManagerSystem();
		//! @brief Default copy ctor
		SoundManagerSystem(const SoundManagerSystem &) = default;
		//! @brief Default dtor
		~SoundManagerSystem() override = default;
		//! @brief A SoundManager screen system can't be assigned.
		SoundManagerSystem &operator=(const SoundManagerSystem &) = delete;
	};
}
