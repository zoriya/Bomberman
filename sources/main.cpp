/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** main
*/


#include <iostream>
#include <cmath>
#include "Wal.hpp"

using namespace std;

int main()
{
	WAL::Wal wal;

	try {
		wal.run();
		return 0;
	} catch (const std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return 84;
	}
}
