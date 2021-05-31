//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "System/System.hpp"
#include <map>

namespace BBM
{
	//! @brief A system to handle Gamepad entities.
	class GamepadSystem : public WAL::System
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		GamepadSystem();
		//! @brief A Gamepad system is copy constructable
		GamepadSystem(const GamepadSystem &) = default;
		//! @brief A default destructor
		~GamepadSystem() override = default;
		//! @brief A Gamepad system is assignable.
		GamepadSystem &operator=(const GamepadSystem &) = default;
	};
}
