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
			enum Layout
			{
				NONE,
				KEYBOARD_0,
				KEYBOARD_1,
				GAMEPAD_0,
				GAMEPAD_1,
				GAMEPAD_2,
				GAMEPAD_3,
				AI
			};

			//! @brief True if the entity should not be controllable.
			bool disabled;

			//! @brief The X and Z abscis of the movement.
			Vector2f move;
			//! @brief input value to select
			bool select = false;
			//! @brief input value for bomb
			bool bomb = false;
			//! @brief input value for pause
			bool pause = false;
			//! @brief The speed applied to every controllable entities.
			float speed = .15f;
			//! @brief The layout used for this controllable.
			Layout layout = NONE;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Initialize a new controllable component.
			explicit ControllableComponent(WAL::Entity &entity);
			//! @brief Initialize a new controllable component.
			ControllableComponent(WAL::Entity &entity, bool isDisabled);
			//! @brief A Controllable component is copy constructable.
			ControllableComponent(const ControllableComponent &) = default;
			//! @brief default destructor
			~ControllableComponent() override = default;
			//! @brief A Controllable component can't be assigned
			ControllableComponent &operator=(const ControllableComponent &) = delete;
	};
}