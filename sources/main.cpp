/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** main
*/


#include <iostream>
#include "Window.hpp"
#include "Drawables/2D/Text.hpp"
#include "Drawables/2D/Circle.hpp"

int main()
{

	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	RAY::Window &window = RAY::Window::getInstance(screenWidth, screenHeight, "Ta mère en slip", false);
	RAY::Drawables::Drawables2D::Text text("Hello World", 10, {190, 200}, RED);
	RAY::Drawables::Drawables2D::Circle circle(400, 225, 50, RED);

	window.open();

	window.setFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.shouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		window.beginDrawing();

		window.clear();

		window.draw(circle);
		window.draw(text);

		window.endDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	window.close();       // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
	/*WAL::Wal wal;

	try {
		wal.run();
		return 0;
	} catch (const std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return 84;
	}*/
}
