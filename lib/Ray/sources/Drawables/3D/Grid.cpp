/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Grid
*/

#include "Drawables/3D/Grid.hpp"
#include <limits.h>
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

	RAY::BoundingBox Grid::getBoundingBox(void) const
	{
		float floatMin = std::numeric_limits<float>::min();
		float floatMax = std::numeric_limits<float>::max();
		RAY::Vector3 min(floatMin, 0, floatMin);
		RAY::Vector3 max(floatMax, 0, floatMax);

		return RAY::BoundingBox(min, max);
	}
}