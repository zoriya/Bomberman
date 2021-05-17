/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Keyboard
*/

#ifndef GAMEPAD_HPP_
#define GAMEPAD_HPP_

#include <raylib.h>
#include <vector>
#include "IController.hpp"

namespace RAY
{

    //! @brief Entity representing a gamepad controller
    class GamePad : public IController {
        public:
            typedef ::GamepadButton Button;

            //! @brief A default constructor
            //! @param The id of the controller 
            GamePad(int id);

            //! @brief A default destructor
            ~GamePad() = override default;

            //! @brief A default copy constructor
            GamePad(const GamePad &) = default;

            //! @brief An entity is assignable
            //! @return A reference to the assigned object
            GamePad &operator=(const GamePad &) = default;

            //! @brief Returns true if Button is pressed on the gamepad
            //! @param Button The keycode of the button
            bool isPressed(Button) override;

            //! @brief Returns true if Button is down on the gamepad
            //! @param Button The keycode of the button
            bool isDown(Button) override;

            //! @brief Returns true if Button is released on the gamepad
            //! @param Button The keycode of the button
            bool isReleased(Button) override;

            //! @brief Returns true if Button is up on the gamepad
            //! @param Button The keycode of the button
            bool isUp(Button) override;

            //! @brief Returns true if controller is available
            bool isAvailable(Button) override;

            //! @brief Sets gamepad's id
            void setID(int id);

            //! @brief Fetch currently pressed buttons
            //! @return Returns a vector containing keycode of currently pressed buttons
            std::vector<GamePad::Button> getPressedButtons(void) override;
        
        private:
            //! @brief The id of the controller, used to fetch buttons' states 
            int _id;
    };
}

#endif /* !KEYBOARD_HPP_ */
