//
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "Components/Health/HealthComponent.hpp"
#include "lib/wal/sources/System/System.hpp"

namespace BBM
{
	class HealthSystem : public WAL::System
	{
	public:
		//! @inherit
		const std::type_info &getComponent() const override;
		//! @inherit
		void onFixedUpdate(Entity &entity) override;

		//! @brief A default constructor
		HealthSystem() = default;
		//! @brief A health system is copy constructable
		HealthSystem(const HealthSystem &) = default;
		//! @brief A default destructor
		~HealthSystem() override = default;
		//! @brief A health system is assignable.
		HealthSystem &operator=(const HealthSystem &) = default;
	}
}