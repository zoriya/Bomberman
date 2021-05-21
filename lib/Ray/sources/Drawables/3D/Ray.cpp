/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Ray
*/

#include "Drawables/3D/Ray.hpp"

RAY::Drawables::Drawables3D::Ray::Ray(const Vector3 &startPosition, const Vector3 &direction, const Color &color):
	ADrawable3D(color), _ray({startPosition, direction})
{

}

const Vector3 &RAY::Drawables::Drawables3D::Ray::getStartPosition(void) const
{
	return this->_ray.position;
}

const Vector3 &RAY::Drawables::Drawables3D::Ray::getDirection(void) const
{
	return this->_ray.direction;
}

RAY::Drawables::Drawables3D::Ray &RAY::Drawables::Drawables3D::Ray::setStartPosition(const Vector3 &startPosition)
{
	this->_ray.position = startPosition;
	return *this;
}

RAY::Drawables::Drawables3D::Ray &RAY::Drawables::Drawables3D::Ray::setDirection(const Vector3 &direction)
{
	this->_ray.direction = direction;
	return *this;
}

void RAY::Drawables::Drawables3D::Ray::drawOn(RAY::Window &)
{
	DrawRay(this->_ray, this->_color.getColor());
}