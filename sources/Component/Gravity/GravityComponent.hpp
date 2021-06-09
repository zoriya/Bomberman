//
// Created by Tom Augier on 2021-05-20.
//

#pragma once

#include <Models/Callback.hpp>
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class GravityComponent : public WAL::Component
	{
		public:

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Constructor
			GravityComponent(WAL::Entity &entity);

			//! @brief A Gravity component can't be instantiated, it should be derived.
			GravityComponent(const GravityComponent &) = default;

			//! @brief default destructor
			~GravityComponent() override = default;

			//! @brief A Gravity component can't be assigned
			GravityComponent &operator=(const GravityComponent &) = delete;
	};
}