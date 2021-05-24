/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Grid
*/

#include "Drawables/3D/Grid.hpp"
#include "Exceptions/RayError.hpp"

RAY::Drawables::Drawables3D::Grid::Grid(int slices, float spacing, const RAY::Color &color):
	ADrawable3D(RAY::Vector3(0, 0, 0), color), _slices(slices), _spacing(spacing)
{

}

int RAY::Drawables::Drawables3D::Grid::getSlices(void) const
{
	return this->_slices;
}

float RAY::Drawables::Drawables3D::Grid::getSpacing(void) const
{
	return this->_spacing;
}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Grid::getPosition(void) const
{
	throw RAY::Exception::NotSupportedError("A Grid does not have a position");
}

RAY::Drawables::Drawables3D::Grid &RAY::Drawables::Drawables3D::Grid::setPosition(const RAY::Vector3 &)
{
	throw RAY::Exception::NotSupportedError("A Grid does not have a position");
}

RAY::Drawables::Drawables3D::Grid &RAY::Drawables::Drawables3D::Grid::setSlices(int slices)
{
	this->_slices = slices;
	return *this;
}

RAY::Drawables::Drawables3D::Grid &RAY::Drawables::Drawables3D::Grid::setSpacing(float spacing)
{
	this->_spacing = spacing;
	return *this;
}

void RAY::Drawables::Drawables3D::Grid::drawOn(RAY::Window &)
{
	DrawGrid(this->_slices, this->_spacing);
}
