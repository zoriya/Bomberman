//
// Created by Louis Auzuret on 06/07/21
//

#pragma once

#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle keyboard entities.
	class IAControllableSystem : public WAL::System
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		IAControllableSystem();
		//! @brief A keyboard system is copy constructable
		IAControllableSystem(const IAControllableSystem &) = default;
		//! @brief A default destructor
		~IAControllableSystem() override = default;
		//! @brief A keyboard system is assignable.
		IAControllableSystem &operator=(const IAControllableSystem &) = default;
	};
}
