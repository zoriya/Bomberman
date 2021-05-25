
/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Keyboard
*/

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include <raylib.h>
#include <vector>

namespace RAY::Controller {
	//! @brief Keyboard event manager
	class Keyboard {
		public:
			typedef ::KeyboardKey Key;

			//! @return true if Key is pressed on the keyboard
			//! @param Key The keycode of the key
			static bool isPressed(Key);

			//! @return true if Key is down on the keyboard
			//! @param Key The keycode of the key
			static bool isDown(Key);

			//! @return true if Key is released on the keyboard
			//! @param Key The keycode of the key
			static bool isReleased(Key);
	
			//! @return true if Key is up on the keyboard
			//! @param Key The keycode of the key
			static bool isUp(Key);
	
			//! @brief Fetch currently pressed keys
			//! @return a vector containing keycode of currently pressed keys
			static std::vector<Keyboard::Key> getPressedKeys(void);

			//! @brief Fetch currently pressed keys
			//! @return a vector containing char of currently pressed keys
			static std::vector<char> getPressedChars(void);
	};
}

#endif /* !KEYBOARD_HPP_ */
