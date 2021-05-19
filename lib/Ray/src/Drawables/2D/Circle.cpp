/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Circle
*/

#include "Drawables/2D/Circle.hpp"

RAY::Drawables::Drawables2D::Circle::Circle(const Vector2 &centerPos, int radius, const Color &color):
    ADrawable2D(centerPos, color), _radius(radius)
{

}

RAY::Drawables::Drawables2D::Circle::Circle(int centerPosX, int centerPosY, int radius, const Color &color):
    ADrawable2D(centerPosX, centerPosY, color), _radius(radius)
{

}

int RAY::Drawables::Drawables2D::Circle::getRadius(void) const
{
    return this->_radius;
}

RAY::Drawables::Drawables2D::Circle &RAY::Drawables::Drawables2D::Circle::setRadius(int radius)
{
    this->_radius = radius;
    return *this;
}

void RAY::Drawables::Drawables2D::Circle::drawOn(RAY::Window &window)
{
    (void)window;
    DrawCircleV(this->_position, this->_radius, this->_color.getColor());
}

void RAY::Drawables::Drawables2D::Circle::drawOn(RAY::Image &image)
{
    ImageDrawCircleV(&(image.getImage()), this->_position, this->_radius, this->_color.getColor());
}
