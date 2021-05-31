/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Line
*/

#include "Drawables/2D/Line.hpp"
#include <cmath>

namespace RAY::Drawables::Drawables2D
{
	Line::Line(const Vector2 &startPosition, const Vector2 &endPosition, const Color &color) :
		ADrawable2D(startPosition, color), _end(endPosition)
	{
	}

	Line::Line(int xStart, int yStart, int xEnd, int yEnd, const Color &color) :
		ADrawable2D(xStart, yStart, color), _end(xEnd, yEnd)
	{
	}

	const RAY::Vector2 &Line::getEndPosition(void) const
	{
		return this->_end;
	}

	Line &Line::setEndPosition(const Vector2 &end)
	{
		this->_end = end;
		return *this;
	}

	void Line::drawOn(RAY::Window &)
	{
		DrawLineV(this->_position, this->_end, this->_color);
	}

	void Line::drawOn(RAY::Image &image)
	{
		ImageDrawLineV(image, this->_position, this->_end, this->_color);
	}
}