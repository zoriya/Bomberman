/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Grid
*/

#include "Drawables/3D/Grid.hpp"
#include "Exceptions/RayError.hpp"

namespace RAY::Drawables::Drawables3D
{

	Grid::Grid(int slices, float spacing, const RAY::Color &color) :
		ADrawable3D(RAY::Vector3(0, 0, 0), color), _slices(slices), _spacing(spacing)
	{
	}

	int Grid::getSlices(void) const
	{
		return this->_slices;
	}

	float Grid::getSpacing(void) const
	{
		return this->_spacing;
	}

	const RAY::Vector3 &Grid::getPosition(void) const
	{
		throw RAY::Exception::NotSupportedError("A Grid does not have a position");
	}

	Grid &Grid::setPosition(const RAY::Vector3 &)
	{
		throw RAY::Exception::NotSupportedError("A Grid does not have a position");
	}

	Grid &Grid::setSlices(int slices)
	{
		this->_slices = slices;
		return *this;
	}

	Grid &Grid::setSpacing(float spacing)
	{
		this->_spacing = spacing;
		return *this;
	}

	void Grid::drawOn(RAY::Window &)
	{
		DrawGrid(this->_slices, this->_spacing);
	}
}