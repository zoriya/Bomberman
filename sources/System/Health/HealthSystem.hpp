//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Health entities.
	class HealthSystem : public WAL::System
	{
	public:
		//! @inherit
		const std::type_info &getComponent() const override;
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		HealthSystem() = default;
		//! @brief A Health system is copy constructable
		HealthSystem(const HealthSystem &) = default;
		//! @brief A default destructor
		~HealthSystem() override = default;
		//! @brief A Health system is assignable.
		HealthSystem &operator=(const HealthSystem &) = default;
	};
}
