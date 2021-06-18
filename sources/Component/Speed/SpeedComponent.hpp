//
// Created by cbihan on 18/06/2021.
//

#pragma once

#include <Component/Component.hpp>

namespace BBM
{
	class SpeedComponent : WAL::Component
	{
	public:
		//! @brief entity speed
		float speed = .15f;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief Initialize a new controllable component.
		explicit SpeedComponent(WAL::Entity &entity);

		//! @brief Initialize a new controllable component.
		explicit SpeedComponent(WAL::Entity &entity, float entitySpeed);
		//! @brief A Controllable component is copy constructable.
		SpeedComponent(const SpeedComponent &) = default;
		//! @brief default destructor
		~SpeedComponent() override = default;
		//! @brief A Controllable component can't be assigned
		SpeedComponent &operator=(const SpeedComponent &) = delete;
	};


}