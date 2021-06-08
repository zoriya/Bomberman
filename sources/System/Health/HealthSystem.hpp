//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include <Component/Bonus/BonusComponent.hpp>
#include "Models/Vector3.hpp"
#include "Wal.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Health entities.
	class HealthSystem : public WAL::System<HealthComponent, PositionComponent>
	{
	private:
        //! @brief Spawn a bonus at the specified position.
		void _createBonus(Vector3f position, BonusComponent::BonusType bonusType, std::chrono::nanoseconds timer);
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<HealthComponent, PositionComponent> &entity) override;

		//! @brief A default constructor
		explicit HealthSystem(WAL::Wal &wal);
		//! @brief A Health system is copy constructable
		HealthSystem(const HealthSystem &) = default;
		//! @brief A default destructor
		~HealthSystem() override = default;
		//! @brief A system is not assignable.
		HealthSystem &operator=(const HealthSystem &) = delete;
	};
}
