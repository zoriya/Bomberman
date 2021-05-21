/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Keyboard
*/

#include "Controllers/Keyboard.hpp"


bool RAY::Controller::Keyboard::isPressed(RAY::Controller::Keyboard::Key key)
{
    return IsKeyPressed(key);
}

bool RAY::Controller::Keyboard::isDown(RAY::Controller::Keyboard::Key key)
{
    return IsKeyDown(key);
}

bool RAY::Controller::Keyboard::isReleased(RAY::Controller::Keyboard::Key key)
{
    return IsKeyReleased(key);
}

bool RAY::Controller::Keyboard::isUp(RAY::Controller::Keyboard::Key key)
{
    return IsKeyUp(key);
}

std::vector<RAY::Controller::Keyboard::Key> RAY::Controller::Keyboard::getPressedKeys(void)
{
    std::vector<RAY::Controller::Keyboard::Key> pressedKeys;

    do {
        pressedKeys.push_back((RAY::Controller::Keyboard::Key)GetKeyPressed());
    } while (pressedKeys.back() != KEY_NULL);
    return pressedKeys;
}

std::vector<char> RAY::Controller::Keyboard::getPressedChars(void)
{
    std::vector<char> pressedChars;

    do {
        pressedChars.push_back(GetCharPressed());
    } while (pressedChars.back() != '\0');
    return pressedChars;
}
