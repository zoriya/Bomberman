//
// Created by Zoe Roux on 5/24/21.
//

#include <Wal.hpp>
#include <iostream>
#include <System/Movable/MovableSystem.hpp>
#include <System/Renderer/RenderScreenSystem.hpp>
#include <System/Renderer/Render2DScreenSystem.hpp>
#include <System/Renderer/Renderer2DSystem.hpp>
#include <Model/Model.hpp>
#include <Drawables/2D/Rectangle.hpp>
#include <Drawables/3D/Cube.hpp>
#include <TraceLog.hpp>
#include <System/Renderer/Renderer3DSystem.hpp>
#include <System/Keyboard/KeyboardSystem.hpp>
#include <System/Controllable/ControllableSystem.hpp>
#include <System/Collision/CollisionSystem.hpp>
#include "Component/Button/ButtonComponent.hpp"
#include <Component/Movable/MovableComponent.hpp>
#include <Component/Collision/CollisionComponent.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <System/Gamepad/GamepadSystem.hpp>
#include "Models/Vector2.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Runner.hpp"
#include "Models/GameState.hpp"
#include "Map/Map.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;
namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	void updateState(WAL::Wal &engine, GameState &state)
	{
		// You can change the scene here or update the game state based on entities values.

		// If you want to keep a scene loaded but not running, store it in the state.loadedScenes.
		//      If you don't need the scene anymore, remember to remove it from the loadedScene array.
		if (RAY::Window::getInstance().shouldClose())
			engine.shouldClose = true;
	}

	void addSystems(WAL::Wal &wal)
	{
		wal.addSystem<KeyboardSystem>()
			.addSystem<GamepadSystem>()
			.addSystem<ControllableSystem>()
			.addSystem<CollisionSystem>(wal)
			.addSystem<MovableSystem>();
	}

	void enableRaylib(WAL::Wal &wal)
	{
		RAY::TraceLog::setLevel(LOG_WARNING);
		RAY::Window &window = RAY::Window::getInstance(600, 400, "Bomberman", FLAG_WINDOW_RESIZABLE);

		wal.addSystem<Renderer3DSystem<RAY3D::Model>>();
		wal.addSystem<Renderer3DSystem<RAY3D::Cube>>();

		wal.addSystem<Render2DScreenSystem>(window)
			.addSystem<Renderer2DSystem<RAY2D::Rectangle>>();
		wal.addSystem<RenderScreenSystem>(window);
	}

	std::shared_ptr<WAL::Scene> loadGameScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		scene->addEntity("first button")
			.addComponent<ButtonComponent>(
			[]() {

			},
			[]() {
				
			},
			[]() {
				
			}
			)
			.addComponent<PositionComponent>(40, 100, 0)
			.addComponent<Drawable2DComponent<RAY2D::Rectangle>>(0, 0, 50, 50, RED);

		scene->addEntity("second button")
			.addComponent<ButtonComponent>(
			[]() {
				
			},
			[]() {
				
			},
			[]() {
				
			}
			)
			.addComponent<PositionComponent>(40, 200, 0)
			.addComponent<Drawable2DComponent<RAY2D::Rectangle>>(0, 0, 50, 50, RED);


		scene->addEntity("camera")
			.addComponent<PositionComponent>(8, 20, 7)
			.addComponent<CameraComponent>(Vector3f(8, 0, 8));
		std::srand(std::time(NULL));
		return scene;
	}

	int run()
	{
		WAL::Wal wal;
		addSystems(wal);
		enableRaylib(wal);
		wal.scene = loadGameScene();

		try {
			wal.run<GameState>(updateState);
			return 0;
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
			return 1;
		}
	}
}