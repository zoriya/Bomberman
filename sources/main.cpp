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
#include "Controllers/Keyboard.hpp"
#include "Camera/Camera3D.hpp"
#include "Drawables/3D/Grid.hpp"
#include "Drawables/3D/Cube.hpp"
#include <cmath>

int main()
{
	SetTraceLogLevel(LOG_WARNING);
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	RAY::Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
	RAY::Window &window = RAY::Window::getInstance(screenWidth, screenHeight, "Ta mère en slip", FLAG_WINDOW_RESIZABLE);
	RAY::Camera::Camera3D camera(RAY::Vector3{30.0f, 20.0f, 30.0f},
	                             RAY::Vector3{0.0f, 0.0f, 0.0f},
	                             RAY::Vector3{0.0f, 1.0f, 0.0f},
	                             70.0,
	                             CAMERA_PERSPECTIVE);
	RAY::Drawables::Drawables3D::Grid grid(10, 5.0f);
	RAY::Drawables::Drawables3D::Cube cube({0}, {0}, {0});

	// Specify the amount of blocks in each direction
	const int numBlocks = 15;

	window.setFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.shouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		double time = GetTime();

		// Calculate time scale for cube position and size
		float scale = (2.0f + (float)sin(time)) * 0.7f;

		// Move camera around the scene
		double cameraTime = time * 0.3;
		camera.setPosition({(float)cos(cameraTime) * 40.0f, 20.0f, (float)sin(cameraTime) * 40.0f});
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		window.beginDrawing();

		window.clear(RAYWHITE);

		window.beginMode3D(camera);

		window.draw(grid);

		for (int x = 0; x < numBlocks; x++) {
			for (int y = 0; y < numBlocks; y++) {
				for (int z = 0; z < numBlocks; z++) {
					// Scale of the blocks depends on x/y/z positions
					float blockScale = (x + y + z) / 30.0f;

					// Scatter makes the waving effect by adding blockScale over time
					float scatter = sinf(blockScale * 20.0f + (float)(time * 4.0f));

					// Calculate the cube position
					cube.setPosition(RAY::Vector3{
						static_cast<float>(x - numBlocks / 2) * (scale * 3.0f) + scatter,
						static_cast<float>(y - numBlocks / 2) * (scale * 2.0f) + scatter,
						static_cast<float>(z - numBlocks / 2) * (scale * 3.0f) + scatter
					});

					// Pick a color with a hue depending on cube position for the rainbow color effect
					cube.setColor(RAY::Color(static_cast<float>(((x + y + z) * 18) % 360), 0.75f, 0.9f));

					// Calculate cube size
					float cubeSize = (2.4f - scale) * blockScale;
					cube.setDimensions({cubeSize, cubeSize, cubeSize});

					// And finally, draw the cube!
					window.draw(cube);
				}
			}
		}

		window.endMode3D();

		window.endDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	window.close();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
