/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** main
*/


#include <iostream>
<<<<<<< Updated upstream
#include <Wal.hpp>
=======
#include <cmath>
#include "Window.hpp"
#include "Drawables/2D/Text.hpp"
#include "Drawables/2D/Circle.hpp"
#include "Controllers/Keyboard.hpp"
#include "Camera/Camera3D.hpp"
#include "Drawables/3D/Grid.hpp"
#include "Drawables/3D/Cube.hpp"
#include "Wal.hpp"
>>>>>>> Stashed changes

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
