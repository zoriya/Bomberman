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
#include "Model/Model.hpp"
#include "Model/ModelAnimations.hpp"
#include "System/Renderer/Renderer3DSystem.hpp"
#include "Component/Drawable/Drawable3DComponent.hpp"
#include "System/Renderer/RenderScreenSystem.hpp"
#include "Vector/Vector3.hpp"
#include "Window.hpp"
#include "TraceLog.hpp"
#include "Wal.hpp"

const std::vector<std::string>textures = {
	"black", "blue", "pink", "red", "white", "yellow"
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

	RAY::TraceLog::setLevel(LOG_WARNING);
	RAY::Window &window = RAY::Window::getInstance(screenWidth, screenHeight, "Bidibidibop", FLAG_WINDOW_RESIZABLE);
	RAY::Image icon("assets/icon.png");
	window.setIcon(icon);
	RAY::Camera::Camera3D camera(RAY::Vector3(10.0f, 10.0f, 10.0f),
	                             RAY::Vector3(0.0f, 0.0f, 0.0f),
	                             RAY::Vector3(0.0f, 1.0f, 0.0f),
	                             45.0f, CAMERA_PERSPECTIVE
	);
	WAL::Entity entityPlayer("roger");
	RAY::Drawables::Drawables3D::Circle circle({30, 30, 30}, 50, 0XFFFFFFF, {0, 0, 0}, 0);
	BBM::Drawable3DComponent<RAY::Drawables::Drawables3D::Circle> circleComponent(entityPlayer, circle);
	BBM::PositionComponent posComponent(entityPlayer, {20, 20, 20});

	BBM::Renderer3DSystem<RAY::Drawables::Drawables3D::Circle> circleSystem(window);

	BBM::RenderScreenSystem<RAY::Camera::Camera3D> renderSystem(window, camera);

	wal.addSystem(circleSystem);
	wal.addSystem(renderSystem);
	entityPlayer.addComponent(circleComponent);
	entityPlayer.addComponent(posComponent);

	camera.setMode(CAMERA_FREE); // Set free camera mode

	float y_rotation = 0;
	window.setFPS(60);

	wal.run<int>([](WAL::Wal &wal, int) {});

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
