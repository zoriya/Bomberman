//
// Created by Zoe Roux on 5/24/21.
//

#include <Wal.hpp>
#include <iostream>
#include "System/Movable/MovableSystem.hpp"
#include "System/Renderer/RenderSystem.hpp"
#include <Model/Model.hpp>
#include <Drawables/2D/Text.hpp>
#include <TraceLog.hpp>
#include "System/Keyboard/KeyboardSystem.hpp"
#include "System/Controllable/ControllableSystem.hpp"
#include "System/Gamepad/GamepadSystem.hpp"
#include <System/Collision/CollisionSystem.hpp>
#include "Runner.hpp"
#include "Models/GameState.hpp"
#include <Model/ModelAnimations.hpp>
#include <System/Timer/TimerSystem.hpp>
#include <System/BombHolder/BombHolderSystem.hpp>
#include <System/Event/EventSystem.hpp>
#include <System/Health/HealthSystem.hpp>
#include <System/Animator/AnimatorSystem.hpp>
#include <System/IntroAnimation/IntroAnimationSystem.hpp>
#include <System/Levitate/LevitateSystem.hpp>
#include <System/Bonus/PlayerBonusSystem.hpp>
#include "System/Animation/AnimationsSystem.hpp"
#include "Map/Map.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include <Drawables/Texture.hpp>
#include <System/Bomb/BombSystem.hpp>
#include <Parser/ParserYaml.hpp>
#include "System/Sound/PlayerSoundManagerSystem.hpp"
#include "System/Sound/MenuSoundManagerSystem.hpp"
#include "System/Music/MusicSystem.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	GameState Runner::gameState;

	void Runner::updateState(WAL::Wal &engine, GameState &state)
	{
		if (RAY::Window::getInstance().shouldClose()) {
			engine.shouldClose = true;
		}
		if (gameState.currentScene == GameState::SceneID::GameScene || gameState.currentScene == GameState::SceneID::SplashScreen) {
			for (auto &[_, component]: engine.getScene()->view<ControllableComponent>()) {
				if (component.pause && gameState.currentScene == GameState::SceneID::GameScene) {
					ParserYAML::save(engine.getScene(), "test");
					gameState.nextScene = GameState::SceneID::PauseMenuScene;
					break;
				} else if (gameState.currentScene == GameState::SceneID::SplashScreen && component.jump) {
					gameState.nextScene = GameState::SceneID::TitleScreenScene;
					break;
				}
			}
		}
		if (gameState.nextScene == gameState.currentScene)
			return;
		gameState._loadedScenes[gameState.currentScene] = engine.getScene();
		engine.changeScene(gameState._loadedScenes[gameState.nextScene]);
		gameState.currentScene = gameState.nextScene;
	}

	void Runner::addSystems(WAL::Wal &wal)
	{
		wal.addSystem<TimerSystem>()
			.addSystem<KeyboardSystem>()
			.addSystem<GamepadSystem>()
			.addSystem<MenuControllableSystem>()
			.addSystem<ControllableSystem>()
			.addSystem<BombHolderSystem>()
			.addSystem<EventSystem>()
			.addSystem<HealthSystem>()
			.addSystem<CollisionSystem>()
			.addSystem<LevitateSystem>()
			.addSystem<PlayerBonusSystem>()
			.addSystem<MovableSystem>()
			.addSystem<BombSystem>()
			.addSystem<PlayerSoundManagerSystem>()
			.addSystem<MenuSoundManagerSystem>()
			.addSystem<IntroAnimationSystem>()
			.addSystem<MusicSystem>();
	}

	void Runner::enableRaylib(WAL::Wal &wal)
	{
		RAY::TraceLog::setLevel(LOG_WARNING);
		RAY::Window &window = RAY::Window::getInstance(1920, 1080, "Bomberman");
		wal.addSystem<AnimationsSystem>()
			.addSystem<AnimatorSystem>()
			.addSystem<RenderSystem>(window);
	}

	void Runner::loadScenes()
	{
		gameState._loadedScenes[GameState::SceneID::MainMenuScene] = loadMainMenuScene();
		gameState._loadedScenes[GameState::SceneID::GameScene] = loadGameScene();
		gameState._loadedScenes[GameState::SceneID::SettingsScene] = loadSettingsMenuScene();
		gameState._loadedScenes[GameState::SceneID::PauseMenuScene] = loadPauseMenuScene();
		gameState._loadedScenes[GameState::SceneID::TitleScreenScene] = loadTitleScreenScene();
		gameState._loadedScenes[GameState::SceneID::CreditScene] = loadCreditScene();
		gameState._loadedScenes[GameState::SceneID::SplashScreen] = loadSplashScreenScene();
	}

	int Runner::run()
	{
		std::srand(std::time(nullptr));
		WAL::Wal wal;
		Runner::addSystems(wal);
		Runner::enableRaylib(wal);
		Runner::loadScenes();
		wal.changeScene(Runner::gameState._loadedScenes[GameState::SceneID::SplashScreen]);

		try {
			wal.run<GameState>(Runner::updateState, Runner::gameState);
			return 0;
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
			return 1;
		}
	}
}