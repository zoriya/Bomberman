//
// Created by cbihan on 01/06/2021.
//

#pragma once

#include <System/System.hpp>

namespace BBM
{
	class AnimationsSystem : public WAL::System
	{
	public:
		//! @inherit
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds) override;

		//! @brief A default constructor
		AnimationsSystem();
		//! @brief A Controllable system is copy constructable
		AnimationsSystem(const AnimationsSystem &) = default;
		//! @brief A default destructor
		~AnimationsSystem() override = default;
		//! @brief A Controllable system is assignable.
		AnimationsSystem &operator=(const AnimationsSystem &) = default;
	};
}