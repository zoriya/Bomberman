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
#include "Drawables/3D/Cylinder.hpp"
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
	"blue", "cyan", "green", "orange", "purple", "red", "yellow"
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
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RAY::Window &window = RAY::Window::getInstance(screenWidth, screenHeight, "raylib [models] example - box collisions");

    // Define the camera to look into our 3d world
    RAY::Camera::Camera3D camera(RAY::Vector3(0.0f, 10.0f, 10.0f), RAY::Vector3(0.0f, 0.0f, 0.0f), RAY::Vector3(0.0f, 1.0f, 0.0f ), 45.0f, RAY::Camera::Projection::CAMERA_PERSPECTIVE);

    RAY::Vector3 playerPosition = { 0.0f, 1.0f, 2.0f };
    RAY::Vector3 playerSize = { 1.0f, 2.0f, 1.0f };
    RAY::Color playerColor = GREEN;

    RAY::Vector3 enemyBoxPos(-4.0f, 1.0f, 0.0f);
    RAY::Vector3 enemyBoxSize(2.0f, 2.0f, 2.0f);

    RAY::Vector3 enemySpherePos(4.0f, 0.0f, 0.0f);
    float enemySphereSize = 1.5f;
	RAY::Drawables::Drawables3D::Grid grid(10, 1.0f);
	RAY::Drawables::Drawables3D::Cube enemy(enemyBoxPos, enemyBoxSize, MAGENTA);
	RAY::Drawables::Drawables3D::Cube player(playerPosition, playerSize, playerColor);
	RAY::Drawables::Drawables3D::Cylinder cylinder(enemySpherePos, 2, 2, 2, MAGENTA);

    bool collision = false;

    window.setFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.shouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Move player
        if (RAY::Controller::Keyboard::isDown(RAY::Controller::Keyboard::Key::KEY_RIGHT)) playerPosition.x += 0.2f;
        else if (RAY::Controller::Keyboard::isDown(RAY::Controller::Keyboard::Key::KEY_LEFT)) playerPosition.x -= 0.2f;
        else if (RAY::Controller::Keyboard::isDown(RAY::Controller::Keyboard::Key::KEY_DOWN)) playerPosition.z += 0.2f;
        else if (RAY::Controller::Keyboard::isDown(RAY::Controller::Keyboard::Key::KEY_UP)) playerPosition.z -= 0.2f;

		player.setPosition(playerPosition);
        collision = RAY::BoundingBox::collision(player, enemy);
		collision = collision || RAY::BoundingBox::collision(player, cylinder);
        // Check collisions player vs enemy-box

        if (collision) player.setColor(RED);
        else player.setColor(GREEN);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        window.setDrawingState(RAY::Window::DRAWING);

            window.clear();

            window.useCamera(camera);

                // Draw enemy-box
				
                window.draw(enemy);

                // Draw enemy-sphere
				window.draw(cylinder);

                // Draw player
                window.draw(player);

                window.draw(grid);        // Draw a grid

            window.unuseCamera();

        window.setDrawingState(RAY::Window::IDLE);
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    window.close();        // Close window and OpenGL context
    //----
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
