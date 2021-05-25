/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Cube
*/

#include "Drawables/3D/Cube.hpp"

namespace RAY::Drawables::Drawables3D
{

	Cube::Cube(const RAY::Vector3 &position, const RAY::Vector3 &dimensions, const Color &color) :
		ADrawable3D(position, color), _dimensions(dimensions)
	{
	}

	const RAY::Vector3 &Cube::getDimensions(void) const
	{
		return this->_dimensions;
	}

	Cube &Cube::setDimensions(const RAY::Vector3 &dimensions)
	{
		this->_dimensions = dimensions;
		return *this;
	}

	void Cube::drawOn(RAY::Window &)
	{
		DrawCubeV(this->_position, this->_dimensions, this->_color);
	}
}