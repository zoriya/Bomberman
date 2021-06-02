/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Triangle
*/

#include "Drawables/2D/Triangle.hpp"
#include "Exceptions/RayError.hpp"

namespace RAY::Drawables::Drawables2D
{

	Triangle::Triangle(const Vector2 &positionA, const Vector2 &positionB, const Vector2 &positionC, const Color &color) :
		ADrawable2D(positionA, color), _posB(positionB), _posC(positionC)
	{
	}

	const RAY::Vector2 &Triangle::getPositionA(void) const
	{
		return this->getPosition();
	}

	const RAY::Vector2 &Triangle::getPositionB(void) const
	{
		return this->_posB;
	}

	const RAY::Vector2 &Triangle::getPositionC(void) const
	{
		return this->_posC;
	}

	Triangle &Triangle::setPositionA(const RAY::Vector2 &position)
	{
		this->_position = position;
		return *this;
	}

	Triangle &Triangle::setPositionB(const RAY::Vector2 &position)
	{
		this->_posB = position;
		return *this;
	}

	Triangle &Triangle::setPositionC(const Vector2 &position)
	{
		this->_posC = position;
		return *this;
	}

	void Triangle::drawOn(RAY::Window &)
	{
		DrawTriangle(this->_position, this->_posB, this->_posC, this->_color);
	}

	void Triangle::drawOn(RAY::Image &)
	{
		throw RAY::Exception::NotSupportedError("An triangle cannot be drawn on an image");
	}

	bool Triangle::isCoordInside(Vector2 coord)
	{
		float A = ((_position.x *(_posB.y-_posC.y) + _posB.x * (_posC.y - _position.y)
	}
}