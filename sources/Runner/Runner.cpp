//
// Created by Zoe Roux on 5/24/21.
//

#include <Wal.hpp>
#include <iostream>
#include "System/Movable/MovableSystem.hpp"
#include "System/Renderer/RenderSystem.hpp"
#include <Model/Model.hpp>
#include <Drawables/3D/Cube.hpp>
#include <TraceLog.hpp>
#include <System/Keyboard/KeyboardSystem.hpp>
#include <System/Controllable/ControllableSystem.hpp>
#include <System/Collision/CollisionSystem.hpp>
#include <Component/Movable/MovableComponent.hpp>
#include <Component/Collision/CollisionComponent.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <System/Gamepad/GamepadSystem.hpp>
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Runner.hpp"
#include "Models/GameState.hpp"
#include <Model/ModelAnimations.hpp>
#include <Component/Animator/AnimatorComponent.hpp>
#include <System/Animator/AnimatorSystem.hpp>
#include "Component/Animation/AnimationsComponent.hpp"
#include "System/Animation/AnimationsSystem.hpp"
#include "Component/Shaders/ShaderComponent.hpp"
#include "Map/Map.hpp"

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
			.addSystem<CollisionSystem>()
			.addSystem<MovableSystem>();
	}

	void enableRaylib(WAL::Wal &wal)
	{
		RAY::TraceLog::setLevel(LOG_WARNING);
		RAY::Window &window = RAY::Window::getInstance(600, 400, "Bomberman", FLAG_WINDOW_RESIZABLE);
		wal.addSystem<AnimationsSystem>()
			.addSystem<AnimatorSystem>()
			.addSystem<RenderSystem>(window);
	}

	std::shared_ptr<WAL::Scene> loadGameScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		scene->addEntity("player")
			.addComponent<PositionComponent>()
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/player/player.iqm", std::make_pair(MAP_DIFFUSE, "assets/player/blue.png"))
			.addComponent<ControllableComponent>()
			.addComponent<AnimatorComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<ShaderComponent>("assets/shaders/glsl330/predator.fs")
			.addComponent<AnimationsComponent>(RAY::ModelAnimations("assets/player/player.iqm"), 3)
			.addComponent<CollisionComponent>(1)
			.addComponent<MovableComponent>()
			.addComponent<HealthComponent>(1, [](WAL::Entity &entity) {
				auto &animation = entity.getComponent<AnimationsComponent>();
				animation.setAnimIndex(5);
			});
		scene->addEntity("camera")
			.addComponent<PositionComponent>(8, 20, 7)
			.addComponent<CameraComponent>(Vector3f(8, 0, 8));
//		scene->addEntity("cube")
//			.addComponent<PositionComponent>(5, 0, 5)
//			.addComponent<Drawable3DComponent, RAY3D::Cube>(Vector3f(-5, 0, -5), Vector3f(3, 3, 3), RED)
//			.addComponent<ControllableComponent>()
//			.addComponent<KeyboardComponent>()
//			.addComponent<CollisionComponent>(WAL::Callback<WAL::Entity &, const WAL::Entity &>(), &MapGenerator::wallCollide, 3);
		std::srand(std::time(nullptr));
		MapGenerator::loadMap(16, 16, MapGenerator::createMap(16, 16), scene);
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