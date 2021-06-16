/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ADrawable2D
*/

#include "Drawables/ADrawable2D.hpp"
#include "Image.hpp"

namespace RAY::Drawables
{

	ADrawable2D::ADrawable2D(const Vector2 &position, const RAY::Color &color, float scale, float rotation) :
		_rotation(rotation),
		_scale(scale),
		_position(position),
		_color(color)
	{
	}


	ADrawable2D::ADrawable2D(int x, int y, const RAY::Color &color, float scale, float rotation) :
		_rotation(rotation),
		_scale(scale),
		_position(static_cast<float>(x), static_cast<float>(y)),
		_color(color)
	{
	}

	const RAY::Vector2 &ADrawable2D::getPosition(void) const
	{
		return this->_position;
	}

	const RAY::Color &ADrawable2D::getColor(void) const
	{
		return this->_color;
	}

	ADrawable2D &ADrawable2D::setPosition(const Vector2 &position)
	{
		this->_position = position;
		return *this;
	}

	ADrawable2D &ADrawable2D::setPosition(int x, int y)
	{
		this->_position.x = static_cast<float>(x);
		this->_position.y = static_cast<float>(y);
		return *this;
	}

	ADrawable2D &ADrawable2D::setColor(const Color &color)
	{
		this->_color = color;
		return *this;
	}

	float ADrawable2D::getScale() const
	{
		return this->_scale;
	}

	void ADrawable2D::setScale(float scale)
	{
		this->_scale = scale;
	}
}