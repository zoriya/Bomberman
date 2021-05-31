//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/System/System.hpp"
#include <map>

namespace BBM
{
	//! @brief A system to handle mouse entities.
	class MouseSystem : public WAL::System
	{
	public:
		//! @inherit
		const std::type_info &getComponent() const override;
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		MouseSystem() = default;
		//! @brief A mouse system is copy constructable
		MouseSystem(const MouseSystem &) = default;
		//! @brief A default destructor
		~MouseSystem() override = default;
		//! @brief A mouse system is assignable.
		MouseSystem &operator=(const MouseSystem &) = default;
	};
}
