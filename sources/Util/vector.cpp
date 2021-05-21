/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Vector
*/

#include "Vector.hpp"
#include "Models/Vector3.hpp"

RAY::Vector3 toRAY(const WAL::Vector3<float> &wal)
{
    return (RAY::Vector3){wal.x, wal.y, wal.y};
}