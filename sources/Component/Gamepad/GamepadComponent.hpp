//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "Controllers/Gamepad.hpp"
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

using Button = RAY::Controller::GamePad::Button;
using Axis = RAY::Controller::GamePad::Axis;
using Gamepad = RAY::Controller::GamePad;

namespace BBM
{
	class GamepadComponent : public WAL::Component
	{
		private:
			//! @brief Identifier of the gamepad, used to fetch events
			int _ID;
		public:
			//! @brief jump key
			Button keyJump = GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
			//! @brief bomb key
			Button keyBomb = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;
			//! @brief pause key
			Button keyPause = GAMEPAD_BUTTON_MIDDLE;
			//! @brief move right key
			Button keyRight = GAMEPAD_BUTTON_LEFT_FACE_RIGHT;
			//! @brief move left key
			Button keyLeft = GAMEPAD_BUTTON_LEFT_FACE_LEFT;
			//! @brief move up key
			Button keyUp = GAMEPAD_BUTTON_LEFT_FACE_UP;
			//! @brief move down key
			Button keyDown = GAMEPAD_BUTTON_LEFT_FACE_DOWN;

			Axis LeftStickX = GAMEPAD_AXIS_LEFT_X;
			Axis LeftStickY = GAMEPAD_AXIS_LEFT_Y;
			Axis RightStickX = GAMEPAD_AXIS_RIGHT_X;
			Axis RightStickY = GAMEPAD_AXIS_RIGHT_Y;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Create a new gampad component using default keys.
			explicit GamepadComponent(WAL::Entity &entity);

			//! @brief Create a new PositionComponent at a certain position
			GamepadComponent(WAL::Entity &entity, int id);

			//! @brief A Gamepad component is copy constructable.
			GamepadComponent(const GamepadComponent &) = default;

			//! @brief default destructor
			~GamepadComponent() override = default;

			//! @brief A Gamepad component can't be assigned
			GamepadComponent &operator=(const GamepadComponent &) = delete;

			//! @brief Set the ID of the Gamepad the events must be fetch from;
			GamepadComponent &setID(int ID);

			//! @brief Get the ID of the Gamepad the events must be fetch from;
			int getID() const; 
	};
}