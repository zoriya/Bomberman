/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Point
*/


#include "Drawables/3D/Point.hpp"

RAY::Drawables::Drawables3D::Point::Point(const Vector3 &position, const Color &color):
	ADrawable3D(color), _position(position)
{

}

const Vector3 &RAY::Drawables::Drawables3D::Point::getPosition(void) const
{
	return this->_position;
}

RAY::Drawables::Drawables3D::Point &RAY::Drawables::Drawables3D::Point::setPosition(const Vector3 &Position)
{
	this->_position = Position;
	return *this;
}

void RAY::Drawables::Drawables3D::Point::drawOn(RAY::Window &)
{
	DrawPoint3D(this->_position, this->_color.getColor());
}
