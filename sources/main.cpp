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
#include <System/Renderer/RenderScreenSystem.hpp>
#include <System/Renderer/Render2DScreenSystem.hpp>
#include <System/Renderer/Renderer2DSystem.hpp>
#include <System/Renderer/Renderer3DSystem.hpp>
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
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

int demo(void)
{
	
	return (0);
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
	//return demo();
	return BBM::run();
}
