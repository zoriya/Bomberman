//
// Created by Arthur Jamet on 2021-05-31.
//

#pragma once

#include "System/System.hpp"
#include <map>
#include "Component/Gamepad/GamepadComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"

namespace BBM
{
	//! @brief A system to handle Gamepad entities.
	class GamepadSystem : public WAL::System<GamepadComponent, ControllableComponent>
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<GamepadComponent, ControllableComponent> &entity) override;

		//! @brief A default constructor
		explicit GamepadSystem(WAL::Wal &wal);
		//! @brief A Gamepad system is copy constructable
		GamepadSystem(const GamepadSystem &) = default;
		//! @brief A default destructor
		~GamepadSystem() override = default;
		//! @brief A system is not assignable.
		GamepadSystem &operator=(const GamepadSystem &) = delete;
	};
}
