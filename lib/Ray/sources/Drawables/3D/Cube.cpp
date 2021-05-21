/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Cube
*/

#include "Drawables/3D/Cube.hpp"


RAY::Drawables::Drawables3D::Cube::Cube(const RAY::Vector3 &position, const RAY::Vector3 &dimensions, const Color &color):
    ADrawable3D(color), _position(position), _dimenstions(dimensions)
{

}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Cube::getPosition(void) const
{
    return this->_position;
}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Cube::getDimensions(void) const
{
    return this->_dimenstions;
}

RAY::Drawables::Drawables3D::Cube &RAY::Drawables::Drawables3D::Cube::setDimensions(const RAY::Vector3 &dimensions)
{
    this->_dimenstions = dimensions;
    return *this;
}

RAY::Drawables::Drawables3D::Cube &RAY::Drawables::Drawables3D::Cube::setPosition(const RAY::Vector3 &position)
{
    this->_position = position;
    return *this;
}

void RAY::Drawables::Drawables3D::Cube::drawOn(RAY::Window &window)
{
    (void)window;
    DrawCubeV(this->_position, this->_dimenstions, this->_color.getColor());
}
