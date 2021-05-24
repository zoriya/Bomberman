/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Vector3
*/

#include "Vector/Vector3.hpp"

RAY::Vector3::Vector3(float X, float Y, float Z):
	x(X), y(Y), z(Z)
{
}

RAY::Vector3::Vector3():
	x(0), y(0), z(0)
{
}

RAY::Vector3::Vector3(const ::Vector3 &vector):
	x(vector.x), y(vector.y), z(vector.z)
{

}

RAY::Vector3::operator ::Vector3() const
{
	::Vector3 v;

	v.x = this->x;
	v.y = this->y;
	v.z = this->z;
	return v;
}