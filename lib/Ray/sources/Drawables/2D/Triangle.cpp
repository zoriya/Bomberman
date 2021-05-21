/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Triangle
*/

#include "Drawables/2D/Triangle.hpp"
#include <exception>

RAY::Drawables::Drawables2D::Triangle::Triangle(const Vector2 &positionA, const Vector2 &positionB, const Vector2 &positionC, const Color &color):
	ADrawable2D(positionA, color), _posB(positionB), _posC(positionC)
{

}

const RAY::Vector2 &RAY::Drawables::Drawables2D::Triangle::getPositionA(void) const
{
	return this->getPosition();
}

const RAY::Vector2 &RAY::Drawables::Drawables2D::Triangle::getPositionB(void) const
{
	return this->_posB;
}

const RAY::Vector2 &RAY::Drawables::Drawables2D::Triangle::getPositionC(void) const
{
	return this->_posC;
}

RAY::Drawables::Drawables2D::Triangle &RAY::Drawables::Drawables2D::Triangle::setPositionA(const RAY::Vector2 &position)
{
	this->_position = position;
	return *this;
}

RAY::Drawables::Drawables2D::Triangle &RAY::Drawables::Drawables2D::Triangle::setPositionB(const RAY::Vector2 &position)
{
	this->_posB = position;
	return *this;
}

RAY::Drawables::Drawables2D::Triangle &RAY::Drawables::Drawables2D::Triangle::setPositionC(const Vector2 &position)
{
	this->_posC = position;
	return *this;
}

void RAY::Drawables::Drawables2D::Triangle::drawOn(RAY::Window &)
{
	DrawTriangle(this->_position, this->_posB, this->_posC, this->_color);
}

void RAY::Drawables::Drawables2D::Triangle::drawOn(RAY::Image &image)
{
	(void)image;
	throw std::exception();
}

