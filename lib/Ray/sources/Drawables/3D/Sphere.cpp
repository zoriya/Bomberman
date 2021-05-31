/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Sphere
*/

#include "Drawables/3D/Sphere.hpp"

namespace RAY::Drawables::Drawables3D
{

	Sphere::Sphere(const Vector3 &centerPosition, int radius, const Color &color) :
		ADrawable3D(centerPosition, color), _radius(radius)
	{
	}

	int Sphere::getRadius(void) const
	{
		return this->_radius;
	}

	Sphere &Sphere::setRadius(int radius)
	{
		this->_radius = radius;
		return *this;
	}

	void Sphere::drawOn(RAY::Window &)
	{
		DrawSphere(this->_position, this->_radius, this->_color);
	}
}