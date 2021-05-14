
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
    class GamePad {
        public:
            typedef ::GamepadButton Button;

            GamePad(int id);

            ~GamePad() = default;

            GamePad(const GamePad &);

            GamePad &operator=(const GamePad &);

            bool isPressed(Button);
            bool isDown(Button);
            bool isReleased(Button);
            bool isUp(Button);
            std::vector<GamePad::Button> getPressedButtons(void);
        
        private:
            int _id;
    };
}

#endif /* !KEYBOARD_HPP_ */
