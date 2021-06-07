//
// Created by Zoe Roux on 5/24/21.
//

#include <Wal.hpp>
#include <iostream>
#include "System/Movable/MovableSystem.hpp"
#include "System/Renderer/RenderSystem.hpp"
#include <Model/Model.hpp>
#include <Drawables/3D/Cube.hpp>
#include <Drawables/2D/Rectangle.hpp>
#include <Drawables/2D/Text.hpp>
#include <TraceLog.hpp>
#include <System/Keyboard/KeyboardSystem.hpp>
#include <System/Controllable/ControllableSystem.hpp>
#include <System/Collision/CollisionSystem.hpp>
#include "Component/Button/ButtonComponent.hpp"
#include <Component/Movable/MovableComponent.hpp>
#include <Component/Collision/CollisionComponent.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <System/Gamepad/GamepadSystem.hpp>
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Runner.hpp"
#include "Models/GameState.hpp"
#include <Model/ModelAnimations.hpp>
#include "Component/Animation/AnimationsComponent.hpp"
#include "System/Animation/AnimationsSystem.hpp"
#include "Map/Map.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include <Drawables/Texture.hpp>

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

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
			.addSystem<MenuControllableSystem>()
			.addSystem<ControllableSystem>()
			.addSystem<CollisionSystem>()
			.addSystem<MovableSystem>();
	}

	void enableRaylib(WAL::Wal &wal)
	{
		RAY::TraceLog::setLevel(LOG_WARNING);
		RAY::Window &window = RAY::Window::getInstance(1920, 1080, "Bomberman");
		wal.addSystem<AnimationsSystem>()
			.addSystem<RenderSystem>(window);
	}

	std::shared_ptr<WAL::Scene> loadTitleScreenScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		scene->addEntity("control")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>();
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
		scene->addEntity("logo")
			.addComponent<PositionComponent>(320, 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/logo_big.png");
		scene->addEntity("text_prompt")
			.addComponent<PositionComponent>(1920 / 5, 1080 - 180, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Press any button to continue", 70, RAY::Vector2(), WHITE)
			.addComponent<ButtonComponent>([](WAL::Entity &entity)
			{
				entity.getComponent<Drawable2DComponent>().drawable->setColor(WHITE);
			},
			[](WAL::Entity &entity)
			{
				entity.getComponent<Drawable2DComponent>().drawable->setColor(ORANGE);
			},
			ButtonComponent::emptyButtonCallback,
			ButtonComponent::emptyButtonCallback);
		//needed material
		//music
		//sound
		return scene;
	}

	std::shared_ptr<WAL::Scene> loadMainMenuScene()
	{
		auto scene = std::make_shared<WAL::Scene>();

		scene->addEntity("Control entity")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>();
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
		scene->addEntity("logo")
			.addComponent<PositionComponent>(1920 / 3, 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/logo_small.png");
		scene->addEntity("play button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 540, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_new_game.png")
			.addComponent<ButtonComponent>([](WAL::Entity &entity)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				
				texture->use("assets/buttons/button_new_game.png");
			}, [](WAL::Entity &entity)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				
				texture->use("assets/buttons/button_new_game_hovered.png");
			},
			ButtonComponent::emptyButtonCallback,
			ButtonComponent::emptyButtonCallback);
		scene->addEntity("settings button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_settings.png")
			.addComponent<ButtonComponent>([](WAL::Entity &entity)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				
				texture->use("assets/buttons/button_settings.png");
			}, [](WAL::Entity &entity)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				
				texture->use("assets/buttons/button_settings_hovered.png");
			},
			ButtonComponent::emptyButtonCallback,
			ButtonComponent::emptyButtonCallback);
		scene->addEntity("exit button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_exit.png")
			.addComponent<ButtonComponent>([](WAL::Entity &entity)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				
				texture->use("assets/buttons/button_exit.png");
			}, [](WAL::Entity &entity)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				
				texture->use("assets/buttons/button_exit_hovered.png");
			},
			ButtonComponent::emptyButtonCallback,
			ButtonComponent::emptyButtonCallback);
		//needed material
		//music
		//sound
		return scene;
	}

	std::shared_ptr<WAL::Scene> loadPauseMenuScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		//needed material
		//return button
		//return button assets
		//settings button
		//settings button assets
		//quit button
		//quit button assets
		//plain background
		//logo
		//music
		//sound
		return scene;
	}

	std::shared_ptr<WAL::Scene> loadSettingsMenuScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		//needed material
		// music logo
		// sound logo
		// plus button
		// minus button
		//mute music logo
		//mute sound logo
		//text for debug
		// ticked box
		// unticked box
		// back button
		// back button asset
		//plain background
		//logo
		//music
		//sound
		return scene;
	}

	std::shared_ptr<WAL::Scene> loadGameScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		scene->addEntity("player")
			.addComponent<PositionComponent>()
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/player/player.iqm", std::make_pair(MAP_DIFFUSE, "assets/player/blue.png"))
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<AnimationsComponent>(RAY::ModelAnimations("assets/player/player.iqm"), 1)
			.addComponent<CollisionComponent>(1)
			.addComponent<MovableComponent>();

		scene->addEntity("camera")
			.addComponent<PositionComponent>(8, 20, 7)
			.addComponent<CameraComponent>(Vector3f(8, 0, 8));
		std::srand(std::time(nullptr));
		MapGenerator::loadMap(16, 16, MapGenerator::createMap(16, 16), scene);
		return scene;
	}

	int run()
	{
		WAL::Wal wal;
		addSystems(wal);
		enableRaylib(wal);
		wal.scene = loadMainMenuScene();

		try {
			wal.run<GameState>(updateState);
			return 0;
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
			return 1;
		}
	}
}