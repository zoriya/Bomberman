//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/System/System.hpp"

namespace Bomberman
{
	//! @brief A system to handle Controllable entities.
	class ControllableSystem : public WAL::System
	{
	public:
		//! @inherit
		const std::type_info &getComponent() const override;
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		ControllableSystem() = default;
		//! @brief A Controllable system is copy constructable
		ControllableSystem(const ControllableSystem &) = default;
		//! @brief A default destructor
		~ControllableSystem() override = default;
		//! @brief A Controllable system is assignable.
		ControllableSystem &operator=(const ControllableSystem &) = default;
	};
}
