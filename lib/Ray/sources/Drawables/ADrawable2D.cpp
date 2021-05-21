/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ADrawable2D
*/

#include "Drawables/ADrawable2D.hpp"

RAY::Drawables::Drawables2D::ADrawable2D::ADrawable2D(const Vector2 &position, const RAY::Color &color):
    _position(position), _color(color)
{

}


RAY::Drawables::Drawables2D::ADrawable2D::ADrawable2D(int x, int y, const RAY::Color &color):
    _position({(float)x, (float)y}), _color(color)
{

}

const Vector2 &RAY::Drawables::Drawables2D::ADrawable2D::getPosition(void) const
{
    return this->_position;
}

const RAY::Color &RAY::Drawables::Drawables2D::ADrawable2D::getColor(void) const
{
    return this->_color;
}

RAY::Drawables::Drawables2D::ADrawable2D &RAY::Drawables::Drawables2D::ADrawable2D::setPosition(const Vector2 &position)
{
    this->_position = position;
    return *this;
}

RAY::Drawables::Drawables2D::ADrawable2D &RAY::Drawables::Drawables2D::ADrawable2D::setPosition(int x, int y)
{
    this->_position.x = x;
    this->_position.y = y;
    return *this;
}

RAY::Drawables::Drawables2D::ADrawable2D &RAY::Drawables::Drawables2D::ADrawable2D::setColor(const Color &color)
{
    this->_color = color;
    return *this;
}
