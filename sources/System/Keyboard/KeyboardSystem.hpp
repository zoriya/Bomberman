//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "System/System.hpp"
#include <map>

namespace BBM
{
	//! @brief A system to handle keyboard entities.
	class KeyboardSystem : public WAL::System
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		KeyboardSystem();
		//! @brief A keyboard system is copy constructable
		KeyboardSystem(const KeyboardSystem &) = default;
		//! @brief A default destructor
		~KeyboardSystem() override = default;
		//! @brief A keyboard system is assignable.
		KeyboardSystem &operator=(const KeyboardSystem &) = default;
	};
}
