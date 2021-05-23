/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Vector
*/

#include "Vector/Vector3.hpp"
#include "Models/Vector3.hpp"

RAY::Vector3 toRAY(const WAL::Vector3f &wal)
{
    return RAY::Vector3(wal.x, wal.y, wal.y);
}