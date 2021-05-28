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

	RAY::BoundingBox Sphere::getBoundingBox(void) const
	{
		RAY::Vector3 min;
		RAY::Vector3 max;

		min.x = this->_position.x - this->_radius;
		min.y = this->_position.y - this->_radius;
		min.z = this->_position.z - this->_radius;

		max.x = this->_position.x + this->_radius;
		max.y = this->_position.y + this->_radius;
		max.z = this->_position.z + this->_radius;

		return RAY::BoundingBox(min, max);
	}
}