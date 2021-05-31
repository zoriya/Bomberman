/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Triangle
*/

#include "Drawables/3D/Triangle.hpp"
#include <exception>

namespace RAY::Drawables::Drawables3D
{

	Triangle::Triangle(const Vector3 &positionA, const Vector3 &positionB, const Vector3 &positionC, const Color &color) :
		ADrawable3D(positionA, color), _posB(positionB), _posC(positionC)
	{
	}

	const RAY::Vector3 &Triangle::getPositionA(void) const
	{
		return this->getPosition();
	}

	const RAY::Vector3 &Triangle::getPositionB(void) const
	{
		return this->_posB;
	}

	const RAY::Vector3 &Triangle::getPositionC(void) const
	{
		return this->_posC;
	}

	Triangle &Triangle::setPositionA(const Vector3 &position)
	{
		this->setPosition(position);
		return *this;
	}

	Triangle &Triangle::setPositionB(const Vector3 &position)
	{
		this->_posB = position;
		return *this;
	}

	Triangle &Triangle::setPositionC(const Vector3 &position)
	{
		this->_posC = position;
		return *this;
	}

	void Triangle::drawOn(RAY::Window &)
	{
		DrawTriangle3D(this->_position, this->_posB, this->_posC, this->_color);
	}
}

