/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Circle
*/

#include "Drawables/3D/Circle.hpp"

RAY::Drawables::Drawables3D::Circle::Circle(const Vector3 &centerPosition, int radius, const Color &color, const Vector3 &rotationAxis, float rotationAngle):
	ADrawable3D(color), _radius(radius), _centerPos(centerPosition), _rotationAxis(rotationAxis), _rotationAngle(rotationAngle)
{

}

int RAY::Drawables::Drawables3D::Circle::getRadius(void) const
{
	return this->_radius;
}

RAY::Drawables::Drawables3D::Circle &RAY::Drawables::Drawables3D::Circle::setRadius(int radius)
{
	this->_radius = radius;
	return *this;
}

const RAY::Vector3 &RAY::Drawables::Drawables3D::Circle::getCenterPos(void) const
{
	return this->_centerPos;
}

void RAY::Drawables::Drawables3D::Circle::drawOn(RAY::Window &)
{
	DrawCircle3D(this->_centerPos, this->_radius,this->_rotationAxis,
	this->_rotationAngle, this->_color);
}