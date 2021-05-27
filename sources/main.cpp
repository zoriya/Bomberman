/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** main
*/


#include <iostream>
#include "Runner/Runner.hpp"

// Dependencies of the demo
#include "Camera/Camera3D.hpp"
#include "Controllers/Keyboard.hpp"
#include "Drawables/2D/Text.hpp"
#include "Drawables/Image.hpp"
#include "Drawables/3D/Grid.hpp"
#include "Drawables/Texture.hpp"
#include "Drawables/3D/Circle.hpp"
#include "Drawables/2D/Circle.hpp"
#include "Drawables/3D/Cube.hpp"
#include "Drawables/3D/Sphere.hpp"
#include "Model/Model.hpp"
#include "Model/ModelAnimations.hpp"
#include "System/Renderer/Renderer3DSystem.hpp"
#include "System/Renderer/Renderer2DSystem.hpp"
#include "Component/Drawable/Drawable3DComponent.hpp"
#include "Component/Drawable/Drawable2DComponent.hpp"
#include "System/Renderer/RenderScreenSystem.hpp"
#include "Vector/Vector3.hpp"
#include "Window.hpp"
#include "TraceLog.hpp"
#include "Wal.hpp"

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

int demo()
{
	WAL::Wal wal;
	const int screenWidth = 800;
	const int screenHeight = 450;
	std::vector<std::string>::const_iterator iterator = textures.begin();
	const std::string modelPath = "assets/player/player.iqm";
	RAY::TraceLog::setLevel(LOG_WARNING);
	RAY::Window &window = RAY::Window::getInstance(screenWidth, screenHeight, "Bidibidibop", FLAG_WINDOW_RESIZABLE);
	RAY::Image icon("assets/icon.png");
	RAY::Vector3 position(0.0f, 0.0f, 0.0f);			// Set model position
	RAY::Drawables::Drawables3D::Model model(modelPath, position, RAY::Vector3(1.0f, 20, 0.0f), -180.0f, RAY::Vector3( 3.0f, 3.0f, 3.0f ));
	RAY::Camera::Camera3D camera(RAY::Vector3(10.0f, 10.0f, 10.0f),
	                             RAY::Vector3(0.0f, 0.0f, 0.0f),
	                             RAY::Vector3(0.0f, 1.0f, 0.0f),
	                             45.0f, CAMERA_PERSPECTIVE
	);
	WAL::Entity entityPlayer("roger");
	RAY::Drawables::Drawables3D::Circle circle({0, 0, 0}, 5, MAROON, {0, 0, 0}, 0);
	BBM::Drawable3DComponent<RAY::Drawables::Drawables3D::Circle> circleComponent(entityPlayer, circle);

	BBM::Renderer3DSystem<RAY::Drawables::Drawables3D::Circle> circleSystem(window);

	wal.addSystem(circleSystem);
	entityPlayer.addComponent(circleComponent);

	RAY::Texture texture(get_full_path(*iterator));
	RAY::ModelAnimations animations(modelPath);
	RAY::Drawables::Drawables3D::Grid grid(10, 1.0f);
	RAY::Drawables::Drawables2D::Text instructionText("PRESS SPACE to PLAY MODEL ANIMATION", 10, {10, 20} , MAROON);
	size_t animationIndex = 0;

	model.setTextureToMaterial(MAP_DIFFUSE, texture);
	window.setIcon(icon);
	camera.setMode(CAMERA_FREE); // Set free camera mode

	float y_rotation = 0;
	window.setFPS(60);

	while (!window.shouldClose())
	{
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
		window.setDrawingState(RAY::Window::DRAWING);
			window.clear();
			window.useCamera(camera);

				window.draw(model);

				window.draw(grid);
				window.draw(circle);
			window.unuseCamera();
			window.draw(instructionText);
		window.setDrawingState(RAY::Window::IDLE);
	}
	window.close();


	return 0;
}


void usage(const std::string &bin)
{
	std::cout << "Bomberman." << std::endl
		<< "\tUsage: " << bin << " [options]" << std::endl
		<< "Options:" << std::endl
		<< "\t-h:\tPrint this help message" << std::endl;
}

int main(int argc, char **argv)
{
	if (argc == 2 && std::string(argv[1]) == "-h") {
		usage(argv[0]);
		return 1;
	}
	return demo();
	return BBM::run();
}
