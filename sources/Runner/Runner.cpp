//
// Created by Zoe Roux on 5/24/21.
//

#include <Wal.hpp>
#include <iostream>
#include <System/Movable/MovableSystem.hpp>
#include <System/Renderer/RenderScreenSystem.hpp>
#include <System/Renderer/Render2DScreenSystem.hpp>
#include <System/Renderer/Renderer2DSystem.hpp>
#include <Drawables/2D/Rectangle.hpp>
#include <System/Renderer/Renderer3DSystem.hpp>
#include "Models/Vector2.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Runner.hpp"
#include "Models/GameState.hpp"

namespace BBM
{
	void updateState(WAL::Wal &engine, GameState &state)
	{
		// You can change the scene here or update the game state based on entities values.

		// If you want to keep a scene loaded but not running, store it in the state.loadedScenes.
		//      If you don't need the scene anymore, remember to remove it from the loadedScene array.
	}

	void enableRaylib(WAL::Wal &wal)
	{
		RAY::Window &window = RAY::Window::getInstance(600, 400, "Bomberman", FLAG_WINDOW_RESIZABLE);

//		wal.addSystem<Renderer3DSystem<RAY::Drawables::Drawables3D::Model>>();

		wal.addSystem<Render2DScreenSystem>(window)
		   .addSystem<Renderer2DSystem<RAY::Drawables::Drawables2D::Rectangle>>();
		wal.addSystem<RenderScreenSystem>(window);
	}

	WAL::Scene loadGameScene()
	{
		WAL::Scene scene;
		scene.addEntity("cube")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent<RAY::Drawables::Drawables2D::Rectangle>>(Vector2f(), Vector2f(10, 10), RED);
		scene.addEntity("camera")
			.addComponent<PositionComponent>(10, 10, 10)
			.addComponent<CameraComponent>();
		return scene;
	}

	int run()
	{
		WAL::Scene gameScene = loadGameScene();
		WAL::Wal wal;
		wal.addSystem<MovableSystem>();
		enableRaylib(wal);
		WAL::Scene scene = loadGameScene();
		wal.scene = std::make_shared<WAL::Scene>(scene);


		// wal.scene = loadGameScene();

		try {
			wal.run<GameState>(updateState);
			return 0;
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
			return 1;
		}
	}
}