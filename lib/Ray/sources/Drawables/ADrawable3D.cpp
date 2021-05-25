/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ADrawable3D
*/

#include "Drawables/ADrawable3D.hpp"

namespace RAY::Drawables::Drawables3D
{

	ADrawable3D::ADrawable3D(const RAY::Vector3 &position, const RAY::Color &color) :
		_position(position), _color(color)
	{
	}

	const RAY::Color &ADrawable3D::getColor(void) const
	{
		return this->_color;
	}

	ADrawable3D &ADrawable3D::setColor(const RAY::Color &color)
	{
		this->_color = color;
		return *this;
	}

	const RAY::Vector3 &ADrawable3D::getPosition(void) const
	{
		return this->_position;
	}

	ADrawable3D &ADrawable3D::setPosition(const RAY::Vector3 &position)
	{
		this->_position = position;
		return *this;
	}
}