
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

namespace Ray {
    class Mouse {
        public:
            typedef ::MouseButton Button;

            //! @return true if Key is pressed on the keyboard
            //! @param Key The keycode of the key
            static bool isPressed(Button);

            //! @return true if Key is down on the keyboard
            //! @param Key The keycode of the key
            static bool isDown(Button);

            //! @return true if Key is released on the keyboard
            //! @param Key The keycode of the key
            static bool isReleased(Button);

            //! @return true if Key is up on the keyboard
            //! @param Key The keycode of the key
            static bool isUp(Button);

            //! @brief Fetch currently pressed buttons
            //! @return a vector containing keycode of currently pressed buttons
            static std::vector<Mouse::Button> getPressedButtons(void);
    };
}

#endif /* !KEYBOARD_HPP_ */
