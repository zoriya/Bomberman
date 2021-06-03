//
// Created by hbenjamin on 03/06/2021.
//

#pragma once

#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Health entities.
	class AnimatorSystem : public WAL::System
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		AnimatorSystem();
		//! @brief A Health system is copy constructable
		AnimatorSystem(const AnimatorSystem &) = default;
		//! @brief A default destructor
		~AnimatorSystem() override = default;
		//! @brief A Health system is assignable.
		AnimatorSystem &operator=(const AnimatorSystem &) = default;
	};
}