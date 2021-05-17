//
// Created by cbihan on 17/05/2021.
//

#pragma once


namespace RAY
{
	class IController
	{
	public:
		//! @brief Returns true if Button is pressed on the gamepad
		//! @param Button The keycode of the button
		virtual bool isPressed(Button) = 0;

		//! @brief Returns true if Button is down on the gamepad
		//! @param Button The keycode of the button
		virtual bool isDown(Button) = 0;

		//! @brief Returns true if Button is released on the gamepad
		//! @param Button The keycode of the button
		virtual bool isReleased(Button) = 0;

		//! @brief Returns true if Button is up on the gamepad
		//! @param Button The keycode of the button
		virtual bool isUp(Button) = 0;

		//! @brief Returns true if controller is available
		virtual bool isAvailable(Button) = 0;

		//! @brief Fetch currently pressed buttons
		//! @return Returns a vector containing keycode of currently pressed buttons
		virtual std::vector<GamePad::Button> getPressedButtons(void) = 0;

		virtual ~IController() = default;
	};
}