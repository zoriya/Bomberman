/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Color
*/

#include "Color.hpp"

RAY::Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    this->setA(a);
    this->setB(b);
    this->setR(r);
    this->setG(g);
}

RAY::Color::Color(const ::Color &color)
{
    _color = color;
}

RAY::Color::Color(int hexValue)
{
    this->setR(hexValue & 0xff000000);
    this->setG(hexValue & 0xff0000);
    this->setB(hexValue & 0xff00);
    this->setA(hexValue & 0xff);
}

RAY::Color &RAY::Color::setR(unsigned char r)
{
    _color.r = r;
    return *this;
}


RAY::Color &RAY::Color::setG(unsigned char g)
{
    _color.g = g;
    return *this;
}


RAY::Color &RAY::Color::setB(unsigned char b)
{
    _color.b = b;
    return *this;
}

RAY::Color &RAY::Color::setA(unsigned char a)
{
    _color.a = a;
    return *this;
}

unsigned char RAY::Color::getR(void) const
{
    return _color.r;
}

unsigned char RAY::Color::getG(void) const
{
    return _color.g;
}

unsigned char RAY::Color::getB(void) const
{
    return _color.b;
}

unsigned char RAY::Color::getA(void) const
{
    return _color.a;
}

const ::Color &RAY::Color::getColor(void) const
{
    return _color;
}

int RAY::Color::toHex(void) const
{
    int c = 0;

    c += _color.a;
    c += _color.b * 0xff;
    c += _color.g * 0xff * 0xff;
    c += _color.r * 0xff * 0xff * 0xff;
    return c;
}