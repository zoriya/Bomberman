/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Color
*/

#include "Color.hpp"

namespace RAY
{
	Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		this->setR(r);
		this->setG(g);
		this->setB(b);
		this->setA(a);
	}

	Color::Color(const ::Color &color)
		: _color(color)
	{
	}

	Color::Color(unsigned int hexValue)
	{
		this->setR(hexValue & 0xff000000);
		this->setG(hexValue & 0xff0000);
		this->setB(hexValue & 0xff00);
		this->setA(hexValue & 0xff);
	}

	Color &Color::setR(unsigned char r)
	{
		this->_color.r = r;
		return *this;
	}

	Color &Color::setG(unsigned char g)
	{
		this->_color.g = g;
		return *this;
	}

	Color &Color::setB(unsigned char b)
	{
		this->_color.b = b;
		return *this;
	}

	Color &Color::setA(unsigned char a)
	{
		this->_color.a = a;
		return *this;
	}

	unsigned char Color::getR(void) const
	{
		return this->_color.r;
	}

	unsigned char Color::getG(void) const
	{
		return this->_color.g;
	}

	unsigned char Color::getB(void) const
	{
		return this->_color.b;
	}

	unsigned char Color::getA(void) const
	{
		return this->_color.a;
	}

	const ::Color &Color::getColor(void) const
	{
		return this->_color;
	}

	int Color::toHex(void) const
	{
		int c = this->_color.a;

		c += this->_color.b << 8;
		c += this->_color.g << 8 * 2;
		c += this->_color.r << 8 * 3;
		return c;
	}
}