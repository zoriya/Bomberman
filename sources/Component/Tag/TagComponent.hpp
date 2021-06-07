//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class TagComponent : public WAL::Component
	{
		public:

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Create a new keyboard component using default keys.
			explicit KeyboardComponent(WAL::Entity &entity);

			//! @brief A Keyboard component is copy constructable.
			KeyboardComponent(const KeyboardComponent &) = default;

			//! @brief default destructor
			~KeyboardComponent() override = default;

			//! @brief A Keyboard component can't be assigned
			KeyboardComponent &operator=(const KeyboardComponent &) = delete;
	};
}