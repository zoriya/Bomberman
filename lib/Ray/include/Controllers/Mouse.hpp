
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

            static bool isPressed(Button);
            static bool isDown(Button);
            static bool isReleased(Button);
            static bool isUp(Button);
            static std::vector<Mouse::Button> getPressedButtons(void);
    };
}

#endif /* !KEYBOARD_HPP_ */
