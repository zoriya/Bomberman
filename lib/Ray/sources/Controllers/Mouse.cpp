/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Mouse
*/

#include "Controllers/Mouse.hpp"

bool RAY::Controller::Mouse::isPressed(RAY::Controller::Mouse::Button button)
{
    return IsMouseButtonPressed(button);
}

bool RAY::Controller::Mouse::isDown(RAY::Controller::Mouse::Button button)
{
    return IsMouseButtonDown(button);
}

bool RAY::Controller::Mouse::isReleased(RAY::Controller::Mouse::Button button)
{
    return IsMouseButtonReleased(button);
}

bool RAY::Controller::Mouse::isUp(RAY::Controller::Mouse::Button button)
{
    return IsMouseButtonUp(button);
}

Vector2 RAY::Controller::Mouse::getCursorPosition(void)
{
    return GetMousePosition();
}

