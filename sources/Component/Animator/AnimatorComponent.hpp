//
// Created by hbenjamin on 03/06/2021.
//

#pragma once

#include <Entity/Entity.hpp>

namespace BBM {
	class AnimatorComponent : public WAL::Component
	{
		public:
			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief An Animator component can't be instantiated, it should be derived.
			explicit AnimatorComponent(WAL::Entity &entity);

			//! @brief An Animator component can't be instantiated, it should be derived.
			AnimatorComponent(const AnimatorComponent &) = default;

			//! @brief default destructor
			~AnimatorComponent() override = default;

			//! @brief An Animator component can't be assigned
			AnimatorComponent &operator=(const AnimatorComponent &) = delete;
	};
}