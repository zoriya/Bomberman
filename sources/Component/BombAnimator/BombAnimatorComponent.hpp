//
// Created by hbenjamin on 07/06/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM {
	class BombAnimatorComponent : public WAL::Component{
	public:

		//! @brief The number of seconds of each animation. This variable is used to reset the nextAnimationRate value.
		std::chrono::nanoseconds animationRate = 1000ms;
		//! @brief The number of nanosecond before the next animation.
		std::chrono::nanoseconds nextAnimationRate = animationRate;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief ctor
		explicit BombAnimatorComponent(WAL::Entity &entity);
		//! @brief copy ctor
		BombAnimatorComponent(const BombAnimatorComponent &) = default;
		//! @brief dtor
		~BombAnimatorComponent() override = default;
		//! @brief assignment operator
		BombAnimatorComponent &operator=(const BombAnimatorComponent &) = delete;
	};
}