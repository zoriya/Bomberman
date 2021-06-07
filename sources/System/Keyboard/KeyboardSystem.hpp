//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "System/System.hpp"
#include <map>
#include "Component/Keyboard/KeyboardComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"

namespace BBM
{
	//! @brief A system to handle keyboard entities.
	class KeyboardSystem : public WAL::System<KeyboardComponent, ControllableComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<KeyboardComponent, ControllableComponent> &entity, std::chrono::nanoseconds) override;

		//! @brief A default constructor
		explicit KeyboardSystem(WAL::Wal &wal);
		//! @brief A keyboard system is copy constructable
		KeyboardSystem(const KeyboardSystem &) = default;
		//! @brief A default destructor
		~KeyboardSystem() override = default;
		//! @brief A system is not assignable.
		KeyboardSystem &operator=(const KeyboardSystem &) = delete;
	};
}
