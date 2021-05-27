/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Circle
*/

#include "Drawables/3D/Circle.hpp"

namespace RAY::Drawables::Drawables3D
{

	Circle::Circle(const Vector3 &centerPosition, int radius, const Color &color, const Vector3 &rotationAxis, float rotationAngle) :
		ADrawable3D(centerPosition, color), _radius(radius), _rotationAxis(rotationAxis), _rotationAngle(rotationAngle)
	{
	}

	int Circle::getRadius(void) const
	{
		return this->_radius;
	}

	Circle &Circle::setRadius(int radius)
	{
		this->_radius = radius;
		return *this;
	}

	const RAY::Vector3 &Circle::getCenterPos(void) const
	{
		return this->_position;
	}

	void Circle::drawOn(RAY::Window &)
	{
		DrawCircle3D(this->_position, this->_radius, this->_rotationAxis,
		             this->_rotationAngle, this->_color);
	}

	RAY::BoundingBox Circle::getBoundingBox(void)
	{
		RAY::Mesh mesh = GenMeshSphere(_radius, _radius, 1);
		return GetMeshBoundingBox(mesh);
	}
}
