/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Line
*/

#include "Drawables/2D/Line.hpp"
#include <cmath>


RAY::Drawables::Drawables2D::Line::Line(const Vector2 &startPosition, const Vector2 &endPosition, const Color &color):
	ADrawable2D(startPosition, color), _end(endPosition)
{

}

RAY::Drawables::Drawables2D::Line::Line(int xStart, int yStart, int xEnd, int yEnd, const Color &color):
	ADrawable2D(xStart, yStart, color), _end(xEnd, yEnd)
{

}

const RAY::Vector2 &RAY::Drawables::Drawables2D::Line::getEndPosition(void) const
{
	return this->_end;
}

RAY::Drawables::Drawables2D::Line &RAY::Drawables::Drawables2D::Line::setEndPosition(const Vector2 &end)
{
	this->_end = end;
	return *this;
}

void RAY::Drawables::Drawables2D::Line::drawOn(RAY::Window &)
{
	DrawLineV(this->_position, this->_end, this->_color.getColor());
}

void RAY::Drawables::Drawables2D::Line::drawOn(RAY::Image &image)
{
	ImageDrawLineV(&(image.getImage()), this->_position, this->_end, this->_color.getColor());
}
