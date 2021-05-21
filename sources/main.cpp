#include <iostream>
#include "Wal.hpp"
#include "Window.hpp"

int main()
{

	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	RAY::Window w(screenWidth, screenHeight, "Arthur it works", true);

//	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	w.setFPS(60);
	//SetTargetFPS(60);          // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!w.shouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		w.beginDrawing();

		w.clear(RAYWHITE);

		DrawText("Congrats! You created your first window !", 190, 200, 20, LIGHTGRAY);

		w.endDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	w.close();       // Close window and OpenGL context
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
