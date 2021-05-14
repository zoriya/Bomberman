
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
    class Keyboard {
        public:
            typedef ::KeyboardKey Key;

            static bool isPressed(Key);
            static bool isDown(Key);
            static bool isReleased(Key);
            static bool isUp(Key);
            static std::vector<Keyboard::Key> getPressedKeys(void);
            static std::vector<char> getPressedChars(void);
    };
}

#endif /* !KEYBOARD_HPP_ */
