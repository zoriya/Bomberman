/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Ray
*/

#include "Drawables/3D/Ray.hpp"

namespace RAY::Drawables::Drawables3D
{

	Ray::Ray(const Vector3 &startPosition, const Vector3 &direction, const Color &color) :
		ADrawable3D(startPosition, color), _direction(direction)
	{
	}

	const RAY::Vector3 &Ray::getDirection(void) const
	{
		return this->_direction;
	}

	Ray &Ray::setDirection(const Vector3 &direction)
	{
		this->_direction = direction;
		return *this;
	}

	void Ray::drawOn(RAY::Window &)
	{
		DrawRay({this->_position, this->_direction}, this->_color);
	}
}