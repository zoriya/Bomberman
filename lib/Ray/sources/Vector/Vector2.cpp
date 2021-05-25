/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Vector2
*/

#include "Vector/Vector2.hpp"

RAY::Vector2::Vector2(float X, float Y):
	x(X), y(Y)
{
}

RAY::Vector2::Vector2():
	x(0), y(0)
{
}

RAY::Vector2::Vector2(const ::Vector2 &vector):
	x(vector.x), y(vector.y)
{

}

RAY::Vector2::operator ::Vector2() const
{
	::Vector2 v;

	v.x = this->x;
	v.y = this->y;
	return v;
}