//
// Created by hbenjamin on 07/06/2021.
//

#pragma once

#include "Component/Animation/AnimationsComponent.hpp"
#include "Component/BombAnimator/BombAnimatorComponent.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle BombAnimator entities.
	class BombAnimatorSystem : public WAL::System<BombAnimatorComponent, AnimationsComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<BombAnimatorComponent, AnimationsComponent> &entity, std::chrono::nanoseconds dTime) override;

		//! @brief A default constructor
		BombAnimatorSystem(WAL::Wal &wal);
		//! @brief An BombAnimator system is copy constructable
		BombAnimatorSystem(const BombAnimatorSystem &) = default;
		//! @brief A default destructor
		~BombAnimatorSystem() override = default;
		//! @brief A BombAnimator system is assignable.
		BombAnimatorSystem &operator=(const BombAnimatorSystem &) = default;
	};
}
