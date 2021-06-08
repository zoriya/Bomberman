/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Gamepad
*/

#include "Controllers/Gamepad.hpp"

RAY::Controller::GamePad::GamePad(int id):
	_id(id)
{
}


bool RAY::Controller::GamePad::isPressed(RAY::Controller::GamePad::Button button)
{
	return IsGamepadButtonPressed(this->_id, button);
}

bool RAY::Controller::GamePad::isDown(RAY::Controller::GamePad::Button button)
{
	return IsGamepadButtonDown(this->_id, button);
}

bool RAY::Controller::GamePad::isReleased(RAY::Controller::GamePad::Button button)
{
	return IsGamepadButtonReleased(this->_id, button);
}

bool RAY::Controller::GamePad::isUp(RAY::Controller::GamePad::Button button)
{
	return IsGamepadButtonUp(this->_id, button);
}

bool RAY::Controller::GamePad::isAvailable()
{
	return IsGamepadAvailable(this->_id);
}

void RAY::Controller::GamePad::setID(int id)
{
	this->_id = id;
}

float RAY::Controller::GamePad::getAxisValue(int index)
{
	return GetGamepadAxisMovement(this->_id, index);
}