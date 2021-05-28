/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Line
*/

#include "Drawables/3D/Plane.hpp"

namespace RAY::Drawables::Drawables3D
{

	Plane::Plane(const Vector3 &position, const Vector2 &dimensions, const Color &color) :
		ADrawable3D(position, color), _dimensions(dimensions)
	{
	}

	const RAY::Vector2 &Plane::getDimensions(void) const
	{
		return this->_dimensions;
	}

	Plane &Plane::setDimensions(const Vector2 &dimensions)
	{
		this->_dimensions = dimensions;
		return *this;
	}

	void Plane::drawOn(RAY::Window &)
	{
		DrawPlane(this->_position, this->_dimensions, this->_color);
	}

	RAY::BoundingBox Plane::getBoundingBox(void) const
	{
		RAY::Vector3 min;
		RAY::Vector3 max;

		min.x = this->_position.x - this->_dimensions.x / 2;
		min.y = this->_position.y;
		min.z = this->_position.z - this->_dimensions.y / 2;

		max.x = this->_position.x + this->_dimensions.x / 2;
		max.y = this->_position.y;
		max.z = this->_position.z + this->_dimensions.y / 2;

		return RAY::BoundingBox(min, max);
	}
}