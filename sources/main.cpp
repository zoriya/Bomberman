/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** main
*/


#include "Wal.hpp"
#include "Camera/Camera3D.hpp"
#include "Controllers/Keyboard.hpp"
#include "Drawables/2D/Text.hpp"
#include "Drawables/Image.hpp"
#include "Drawables/3D/Grid.hpp"
#include "Drawables/Texture.hpp"
#include "Drawables/2D/Circle.hpp"
#include "Model/Model.hpp"
#include "Model/ModelAnimations.hpp"
#include "System/Renderer/Renderer2DSystem.hpp"
#include "Component/Drawable/Drawable2DComponent.hpp"
#include "Vector/Vector3.hpp"
#include "Window.hpp"
#include "TraceLog.hpp"

const std::vector<std::string>textures = {
	"blue", "cyan", "green", "purple", "red", "yellow"
};

std::string get_full_path(const std::string &color)
{
	std::string path = "assets/player/";

	path += color;
	path += ".png";
	return path;
}

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	std::vector<std::string>::const_iterator iterator = textures.begin();
	const std::string modelPath = "assets/player/player.iqm";
	RAY::TraceLog::setLevel(LOG_WARNING);
	RAY::Window &window = RAY::Window::getInstance(screenWidth, screenHeight, "Bidibidibop", FLAG_WINDOW_RESIZABLE);
	RAY::Image icon("assets/icon.png");
	RAY::Model model(modelPath);
	RAY::Camera::Camera3D camera(RAY::Vector3(10.0f, 10.0f, 10.0f),
								 RAY::Vector3(0.0f, 0.0f, 0.0f),
								 RAY::Vector3(0.0f, 1.0f, 0.0f),
								 45.0f, CAMERA_PERSPECTIVE
								);
	RAY::Texture texture(get_full_path(*iterator));
	RAY::ModelAnimations animations(modelPath);
	RAY::Drawables::Drawables3D::Grid grid(10, 1.0f);
	RAY::Drawables::Drawables2D::Text instructionText("PRESS SPACE to PLAY MODEL ANIMATION", 10, {10, 20} , MAROON);
	size_t animationIndex = 0;
	RAY::Vector3 position(0.0f, 0.0f, 0.0f);			// Set model position

	model.setTextureToMaterial(MAP_DIFFUSE, texture);
	window.setIcon(icon);
	camera.setMode(CAMERA_FREE); // Set free camera mode

	float y_rotation = 0;
	window.setFPS(60);				   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.shouldClose())		// Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		camera.update();

		// Play animation when spacebar is held down
		if (RAY::Controller::Keyboard::isDown(KEY_SPACE))
		{
			animations[animationIndex].incrementFrameCounter();
			model.setAnimation(animations[animationIndex]);
		}
		if (RAY::Controller::Keyboard::isReleased(KEY_UP))
		{
			++iterator;
			if (iterator == textures.end())
				iterator = textures.begin();
			texture.unload();
			texture.load(get_full_path(*iterator));
			model.setTextureToMaterial(MAP_DIFFUSE, texture);
		}
		if (RAY::Controller::Keyboard::isReleased(KEY_LEFT))
		{
			animationIndex = --animationIndex % animations.getAnimationsCount();
			model.setAnimation(animations[animationIndex]);
		}
		if (RAY::Controller::Keyboard::isReleased(KEY_RIGHT))
		{
			animationIndex = ++animationIndex % animations.getAnimationsCount();
			model.setAnimation(animations[animationIndex]);
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		window.setDrawingState(RAY::Window::DRAWING);

			window.clear();

			window.useCamera(camera);

				window.draw(model, position, RAY::Vector3(1.0f, 20, 0.0f), -180.0f, RAY::Vector3( 3.0f, 3.0f, 3.0f ));

				window.draw(grid);

			window.unuseCamera();

			window.draw(instructionText);

		window.setDrawingState(RAY::Window::IDLE);
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------

	window.close();			  // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
