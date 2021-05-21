
/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Keyboard
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include <raylib.h>
#include <vector>

namespace RAY::Controller {
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

            //! @return A 2D vector holding the current position of the cursor
            static Vector2 getCursorPosition(void);
    };
}

#endif /* !KEYBOARD_HPP_ */
