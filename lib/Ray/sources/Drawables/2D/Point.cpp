/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Point
*/

#include "Drawables/2D/Point.hpp"

RAY::Drawables::Drawables2D::Point::Point(const Vector2 &position, const Color &color):
	ADrawable2D(position, color)
{

}

RAY::Drawables::Drawables2D::Point::Point(int x, int y, const Color &color):
	ADrawable2D(x, y, color)
{

}

void RAY::Drawables::Drawables2D::Point::drawOn(RAY::Window &)
{
	DrawPixel(this->_position.x, this->_position.y, this->_color.getColor());
}

void RAY::Drawables::Drawables2D::Point::drawOn(RAY::Image &image)
{
	ImageDrawPixel(&(image.getImage()), this->_position.x, this->_position.y, this->_color.getColor());
}

