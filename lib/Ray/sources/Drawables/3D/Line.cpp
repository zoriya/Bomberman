/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Line
*/

#include "Drawables/3D/Line.hpp"

RAY::Drawables::Drawables3D::Line::Line(const Vector3 &startPosition, const Vector3 &endPosition, const Color &color):
	ADrawable3D(color), _startPosition(startPosition), _endPosition(endPosition)
{

}


const Vector3 &RAY::Drawables::Drawables3D::Line::getStartPosition(void) const
{
	return this->_startPosition;
}

const Vector3 &RAY::Drawables::Drawables3D::Line::getEndPosition(void) const
{
	return this->_endPosition;
}

RAY::Drawables::Drawables3D::Line &RAY::Drawables::Drawables3D::Line::setStartPosition(const Vector3 &startPosition)
{
	this->_startPosition = startPosition;
	return *this;
}

RAY::Drawables::Drawables3D::Line &RAY::Drawables::Drawables3D::Line::setEndPosition(const Vector3 &endPosition)
{
	this->_endPosition = endPosition;
	return *this;
}

void RAY::Drawables::Drawables3D::Line::drawOn(RAY::Window &)
{
	DrawLine3D(this->_startPosition, this->_endPosition, this->_color.getColor());
}
