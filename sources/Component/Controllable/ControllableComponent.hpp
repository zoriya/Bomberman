//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class ControllableComponent : public WAL::Component
	{	
		public:
			//! @brief input value for X axe
			float moveX = 0;
			//! @brief input value for Z axe
			float moveZ = 0;
			//! @brief input value for jump
			bool jump = false;
			//! @brief input value for bomb
			bool bomb = false;
			//! @brief input value for pause
			bool pause = false;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Initialize a new controllable component.
			explicit ControllableComponent(WAL::Entity &entity);
			//! @brief A Controllable component is copy constructable.
			ControllableComponent(const ControllableComponent &) = default;
			//! @brief default destructor
			~ControllableComponent() override = default;
			//! @brief A Controllable component can't be assigned
			ControllableComponent &operator=(const ControllableComponent &) = delete;
	};
}