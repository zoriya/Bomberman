/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Cube
*/

#include "Drawables/3D/Cube.hpp"


RAY::Drawables::Drawables3D::Cube::Cube(const RAY::Vector3 &position, const RAY::Vector3 &dimensions, const Color &color):
	ADrawable3D(color), _position(position), _dimensions(dimensions)
{

}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Cube::getPosition(void) const
{
	return this->_position;
}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Cube::getDimensions(void) const
{
	return this->_dimensions;
}

RAY::Drawables::Drawables3D::Cube &RAY::Drawables::Drawables3D::Cube::setDimensions(const RAY::Vector3 &dimensions)
{
	this->_dimensions = dimensions;
	return *this;
}

RAY::Drawables::Drawables3D::Cube &RAY::Drawables::Drawables3D::Cube::setPosition(const RAY::Vector3 &position)
{
	this->_position = position;
	return *this;
}

void RAY::Drawables::Drawables3D::Cube::drawOn(RAY::Window &)
{
	DrawCubeV(this->_position, this->_dimensions, this->_color);
}

RAY::BoundingBox RAY::Drawables::Drawables3D::Cube::getBoundingBox(void)
{
	RAY::Mesh mesh = GenMeshCube(_dimensions.x, _dimensions.y, _dimensions.z);
	return GetMeshBoundingBox(mesh);
}
