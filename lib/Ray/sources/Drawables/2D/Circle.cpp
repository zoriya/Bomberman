/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Circle
*/

#include "Drawables/2D/Circle.hpp"
#include "Drawables/Image.hpp"

namespace RAY::Drawables::Drawables2D
{
	Circle::Circle(const Vector2 &centerPos, int radius, const Color &color) :
		ADrawable2D(centerPos, color), _radius(radius)
	{
	}

	Circle::Circle(int centerPosX, int centerPosY, int radius, const Color &color) :
		ADrawable2D(centerPosX, centerPosY, color), _radius(radius)
	{
	}

	int Circle::getRadius(void) const
	{
		return this->_radius;
	}

	Circle &Circle::setRadius(int radius)
	{
		this->_radius = radius;
		return *this;
	}

	void Circle::drawOn(RAY::Window &)
	{
		DrawCircleV(this->_position, this->_radius, this->_color);
	}

	void Circle::drawOn(RAY::Image &image)
	{
		ImageDrawCircleV(image, this->_position, this->_radius, this->_color);
	}
}