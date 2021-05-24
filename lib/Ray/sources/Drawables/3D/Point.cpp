/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Point
*/


#include "Drawables/3D/Point.hpp"

RAY::Drawables::Drawables3D::Point::Point(const Vector3 &position, const Color &color):
	ADrawable3D(position, color)
{

}

void RAY::Drawables::Drawables3D::Point::drawOn(RAY::Window &)
{
	DrawPoint3D(this->_position, this->_color);
}
