//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include <Models/Vector2.hpp>
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <chrono>

using namespace std::chrono_literals;

namespace BBM
{
	class ControllableComponent : public WAL::Component
	{	
		public:
			//! @brief The X and Z abscis of the movement.
			Vector2f move;
			//! @brief input value for jump
			bool jump = false;
			//! @brief input value for bomb
			bool bomb = false;
			//! @brief input value for pause
			bool pause = false;
			//! @brief The speed applied to every controllable entities.
			float speed = .25f;
			//! @brief The number of seconds before a speedbonus expire. This variable is used to reset the nextSpeedBonusRate value.
			std::chrono::nanoseconds speedBonusRate = 15000ms;
			//! @brief The number of nanosecond before the expiration of a speed bonus.
			std::chrono::nanoseconds nextSpeedBonusRate = speedBonusRate;

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