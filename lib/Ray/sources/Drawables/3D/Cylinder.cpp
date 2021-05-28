/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Cylinder
*/

#include "Drawables/3D/Cylinder.hpp"

namespace RAY::Drawables::Drawables3D
{

	Cylinder::Cylinder(const Vector3 &position, float radiusTop, float radiusBottom, float height, const Color &color) :
		ADrawable3D(position, color), _topRadius(radiusTop), _bottomRadius(radiusBottom), _height(height)
	{
	}

	int Cylinder::getTopRadius(void) const
	{
		return this->_topRadius;
	}

	Cylinder &Cylinder::setTopRadius(float radius)
	{
		this->_topRadius = radius;
		return *this;
	}

	int Cylinder::getBottomRadius(void) const
	{
		return this->_bottomRadius;
	}

	Cylinder &Cylinder::setBottomRadius(float radius)
	{
		this->_bottomRadius = radius;
		return *this;
	}

	float Cylinder::getHeight(void) const
	{
		return this->_height;
	}

	Cylinder &Cylinder::setHeight(float height)
	{
		this->_height = height;
		return *this;
	}

	void Cylinder::drawOn(RAY::Window &)
	{
		DrawCylinder(this->_position, this->_topRadius, this->_bottomRadius, this->_height, 0, this->_color);
	}

	RAY::BoundingBox Cylinder::getBoundingBox(void) const
	{
		RAY::Vector3 min;
		RAY::Vector3 max;
		float maxRadius = this->_bottomRadius > this->_topRadius ? this->_bottomRadius : this->_topRadius;

		min.x = this->_position.x - maxRadius;
		min.y = this->_position.y - maxRadius;
		min.z = this->_position.z - maxRadius;

		max.x = this->_position.x + maxRadius;
		max.y = this->_position.y + maxRadius;
		max.z = this->_position.z + maxRadius;

		return RAY::BoundingBox(min, max);
	}
}