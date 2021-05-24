/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Line
*/

#include "Drawables/3D/Plane.hpp"

RAY::Drawables::Drawables3D::Plane::Plane(const Vector3 &position, const Vector2 &dimensions, const Color &color):
	ADrawable3D(position, color), _dimensions(dimensions)
{

}

const RAY::Vector2 &RAY::Drawables::Drawables3D::Plane::getDimensions(void) const
{
	return this->_dimensions;
}

RAY::Drawables::Drawables3D::Plane &RAY::Drawables::Drawables3D::Plane::setDimensions(const Vector2 &dimensions)
{
	this->_dimensions = dimensions;
	return *this;
}

void RAY::Drawables::Drawables3D::Plane::drawOn(RAY::Window &)
{
	DrawPlane(this->_position, this->_dimensions, this->_color);
}
