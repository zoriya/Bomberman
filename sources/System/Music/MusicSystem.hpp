//
// Created by Tom Augier on 05/06/2021
//

#pragma once

#include "System/System.hpp"
#include "Window.hpp"
#include "Component/Music/MusicComponent.hpp"
#include "Component/Health/HealthComponent.hpp"
#include <Component/Controllable/ControllableComponent.hpp>
#include "Wal.hpp"

namespace BBM
{
	class MusicSystem : public WAL::System<MusicComponent>
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<MusicComponent> &entity) override;
		
		//! @brief ctor
		MusicSystem(WAL::Wal &wal);
		//! @brief Default copy ctor
		MusicSystem(const MusicSystem &) = default;
		//! @brief Default dtor
		~MusicSystem() override = default;
		//! @brief A MusicManager screen system can't be assigned.
		MusicSystem &operator=(const MusicSystem &) = delete;
	};
}
