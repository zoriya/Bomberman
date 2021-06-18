//
// Created by hbenjamin on 07/06/2021.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include "Models/Vector3.hpp"

namespace BBM {
	class LevitateComponent : public WAL::Component {
	public:

		//! @brief Go down or up
		bool up = true;
		//! @brief Original y of the entity
		float y;

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief Create a new levitate component.
		explicit LevitateComponent(WAL::Entity &entity);

		//! @brief Create a new levitate component.
		LevitateComponent(WAL::Entity &entity, float entityY);

		//! @brief A Levitate component is copy constructable.
		LevitateComponent(const LevitateComponent &) = default;

		//! @brief default destructor
		~LevitateComponent() override = default;

		//! @brief A Levitate component can't be assigned
		LevitateComponent &operator=(const LevitateComponent &) = delete;
	};
}