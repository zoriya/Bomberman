/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Point
*/

#include "Drawables/2D/Point.hpp"
#include "Drawables/Image.hpp"

namespace RAY::Drawables::Drawables2D
{

	Point::Point(const Vector2 &position, const Color &color) :
		ADrawable2D(position, color)
	{
	}

	Point::Point(int x, int y, const Color &color) :
		ADrawable2D(x, y, color)
	{
	}

	void Point::drawOn(RAY::Window &)
	{
		DrawPixel(this->_position.x, this->_position.y, this->_color);
	}

	void Point::drawOn(RAY::Image &image)
	{
		ImageDrawPixel(image, this->_position.x, this->_position.y, this->_color);
	}
}
