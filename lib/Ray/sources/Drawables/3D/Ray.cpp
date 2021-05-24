/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Ray
*/

#include "Drawables/3D/Ray.hpp"

RAY::Drawables::Drawables3D::Ray::Ray(const Vector3 &startPosition, const Vector3 &direction, const Color &color):
	ADrawable3D(startPosition, color), _direction(direction)
{

}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Ray::getDirection(void) const
{
	return this->_direction;
}

RAY::Drawables::Drawables3D::Ray &RAY::Drawables::Drawables3D::Ray::setDirection(const Vector3 &direction)
{
	this->_direction = direction;
	return *this;
}

void RAY::Drawables::Drawables3D::Ray::drawOn(RAY::Window &)
{
	::Ray ray = {this->_position, this->_direction};
	DrawRay(ray, this->_color);
}