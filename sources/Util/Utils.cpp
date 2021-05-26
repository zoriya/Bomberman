/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Vector
*/

#include "Vector/Vector3.hpp"
#include "Models/Vector3.hpp"
#include "Utils.hpp"

namespace BBM
{
	RAY::Vector3 Utils::toRAY(const BBM::Vector3f &wal)
	{
		return RAY::Vector3(wal.x, wal.y, wal.y);
	}
}