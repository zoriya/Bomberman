/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Triangle
*/

#include "Drawables/3D/Triangle.hpp"
#include <exception>

RAY::Drawables::Drawables3D::Triangle::Triangle(const Vector3 &positionA, const Vector3 &positionB, const Vector3 &positionC, const Color &color):
	ADrawable3D(color), _posA(positionA), _posB(positionB), _posC(positionC)
{

}

const Vector3 &RAY::Drawables::Drawables3D::Triangle::getPositionA(void) const
{
	return this->_posA;
}

const Vector3 &RAY::Drawables::Drawables3D::Triangle::getPositionB(void) const
{
	return this->_posB;
}

const Vector3 &RAY::Drawables::Drawables3D::Triangle::getPositionC(void) const
{
	return this->_posC;
}

RAY::Drawables::Drawables3D::Triangle &RAY::Drawables::Drawables3D::Triangle::setPositionA(const Vector3 &position)
{
	this->_posA = position;
	return *this;
}

RAY::Drawables::Drawables3D::Triangle &RAY::Drawables::Drawables3D::Triangle::setPositionB(const Vector3 &position)
{
	this->_posB = position;
	return *this;
}

RAY::Drawables::Drawables3D::Triangle &RAY::Drawables::Drawables3D::Triangle::setPositionC(const Vector3 &position)
{
	this->_posC = position;
	return *this;
}

void RAY::Drawables::Drawables3D::Triangle::drawOn(RAY::Window &)
{
	DrawTriangle3D(this->_posA, this->_posB, this->_posC, this->_color.getColor());
}


