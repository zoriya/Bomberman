/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Rectangle
*/

#include "Drawables/2D/Rectangle.hpp"
#include <cmath>

namespace RAY::Drawables::Drawables2D
{

	Rectangle::Rectangle(const Vector2 &position, const Vector2 &dimensions, const Color &color) :
		ADrawable2D(position, color), _dimensions(dimensions)
	{
	}

	Rectangle::Rectangle(int x, int y, int width, int height, const Color &color) :
		ADrawable2D(x, y, color), _dimensions(width, height)
	{
	}

	const RAY::Vector2 &Rectangle::getDimensions(void)
	{
		return this->_dimensions;
	}

	Rectangle &Rectangle::setDimensions(const Vector2 &dimensions)
	{
		this->_dimensions = dimensions;
		return *this;
	}

	Rectangle &Rectangle::setDimensions(int x, int y)
	{
		this->_dimensions.x = x;
		this->_dimensions.y = y;
		return *this;
	}

	void Rectangle::drawOn(RAY::Window &)
	{
		DrawRectangleV(this->_position, this->_dimensions, this->_color);
	}

	void Rectangle::drawOn(RAY::Image &image)
	{
		ImageDrawRectangleV(image, this->_position, this->_dimensions, this->_color);
	}
}