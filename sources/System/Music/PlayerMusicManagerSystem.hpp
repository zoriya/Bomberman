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
	class MusicManagerSystem : public WAL::System
	{
	public:
        //! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;
		
		//! @brief ctor
		MusicManagerSystem(WAL::Wal &wal, RAY::Window &window);
		//! @brief Default copy ctor
		MusicManagerSystem(const MusicManagerSystem &) = default;
		//! @brief Default dtor
		~MusicManagerSystem() override = default;
		//! @brief A MusicManager screen system can't be assigned.
		MusicManagerSystem &operator=(const MusicManagerSystem &) = delete;
	};
}
