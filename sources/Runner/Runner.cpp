//
// Created by Zoe Roux on 5/24/21.
//

#include <Wal.hpp>
#include <iostream>
#include "System/Movable/MovableSystem.hpp"
#include "System/Renderer/RenderSystem.hpp"
#include <Drawables/2D/Rectangle.hpp>
#include <TraceLog.hpp>
#include "System/Keyboard/KeyboardSystem.hpp"
#include "System/Controllable/ControllableSystem.hpp"
#include "System/Gamepad/GamepadSystem.hpp"
#include <System/Collision/CollisionSystem.hpp>
#include "Component/Button/ButtonComponent.hpp"
#include <Component/Collision/CollisionComponent.hpp>
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/IAControllable/IAControllableComponent.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <System/Gamepad/GamepadSystem.hpp>
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Runner.hpp"
#include "Models/GameState.hpp"
#include <System/Timer/TimerSystem.hpp>
#include <System/Timer/TimerUISystem.hpp>
#include <System/BombHolder/BombHolderSystem.hpp>
#include <System/Event/EventSystem.hpp>
#include <System/Health/HealthSystem.hpp>
#include <System/Animator/AnimatorSystem.hpp>
#include <Component/Tag/TagComponent.hpp>
#include <System/IntroAnimation/IntroAnimationSystem.hpp>
#include <System/Levitate/LevitateSystem.hpp>
#include <System/Bonus/PlayerBonusSystem.hpp>
#include "System/Shaders/ShaderSystem.hpp"
#include "System/Shaders/ShaderDrawable2DSystem.hpp"
#include "System/Shaders/ShaderModelSystem.hpp"
#include "System/Animation/AnimationsSystem.hpp"
#include "Map/Map.hpp"
#include "System/IAControllable/IAControllableSystem.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include <System/Bomb/BombSystem.hpp>
#include <Parser/ParserYaml.hpp>
#include "System/Sound/PlayerSoundManagerSystem.hpp"
#include "System/Sound/MenuSoundManagerSystem.hpp"
#include "System/Gravity/GravitySystem.hpp"
#include "System/BumperTimer/BumperTimerSystem.hpp"
#include "System/Music/MusicSystem.hpp"
#include "System/Renderer/CameraSystem.hpp"
#include "System/Lobby/LobbySystem.hpp"
#include "System/Score/ScoreSystem.hpp"
#include "System/EndCondition/EndConditionSystem.hpp"
#include "Component/Lobby/LobbyComponent.hpp"
#include "System/Bonus/BonusUISystem.hpp"

namespace BBM
{
	GameState Runner::gameState;
	int Runner::mapWidth = 16;
	int Runner::mapHeight = 16;
	bool Runner::hasHeights = false;

	void Runner::updateState(WAL::Wal &engine, GameState &state)
	{
		auto &view = engine.getScene()->view<ControllableComponent>();
		if (RAY::Window::getInstance().shouldClose())
			engine.shouldClose = true;
		if (gameState.currentScene == GameState::SceneID::GameScene) {
			for (auto &[_, component]: engine.getScene()->view<ControllableComponent>()) {
				if (component.pause && gameState.currentScene == GameState::SceneID::GameScene) {
					gameState.nextScene = GameState::SceneID::PauseMenuScene;
					break;
				}
			}
		}
		if (gameState.nextScene == gameState.currentScene)
			return;
		if (gameState.nextScene == GameState::SceneID::ScoreScene)
			gameState._loadedScenes[GameState::SceneID::ScoreScene] = Runner::loadScoreScene(*engine.getScene());
		gameState._loadedScenes[gameState.currentScene] = engine.getScene();
		engine.changeScene(gameState._loadedScenes[gameState.nextScene]);
		gameState.currentScene = gameState.nextScene;
	}

	void Runner::addSystems(WAL::Wal &wal)
	{
		wal.addSystem<TimerSystem>()
			.addSystem<TimerUISystem>()
			.addSystem<KeyboardSystem>()
			.addSystem<GamepadSystem>()
			.addSystem<IAControllableSystem>()
			.addSystem<LobbySystem>()
			.addSystem<MenuControllableSystem>()
			.addSystem<ControllableSystem>()
			.addSystem<BombHolderSystem>()
			.addSystem<EventSystem>()
			.addSystem<HealthSystem>()
			.addSystem<BonusUISystem>()
			.addSystem<CollisionSystem>()
			.addSystem<LevitateSystem>()
			.addSystem<PlayerBonusSystem>()
			.addSystem<MovableSystem>()
			.addSystem<BombSystem>()
			.addSystem<PlayerSoundManagerSystem>()
			.addSystem<MenuSoundManagerSystem>()
			.addSystem<IntroAnimationSystem>()
			.addSystem<GravitySystem>()
			.addSystem<BumperTimerSystem>()
			.addSystem<ShaderSystem>()
			.addSystem<ShaderModelSystem>()
			.addSystem<ShaderDrawable2DSystem>()
			.addSystem<EndConditionSystem>()
			.addSystem<ScoreSystem>()
			.addSystem<CameraSystem>()
			.addSystem<MusicSystem>();
	}

	void Runner::enableRaylib(WAL::Wal &wal)
	{
		RAY::TraceLog::setLevel(LOG_WARNING);
		RAY::Window &window = RAY::Window::getInstance(1280, 720, "Bomberman", FLAG_WINDOW_RESIZABLE);
		wal.addSystem<AnimationsSystem>()
			.addSystem<AnimatorSystem>()
			.addSystem<RenderSystem>(window);
	}

	void Runner::addMenuControl(WAL::Scene &scene, const std::map<SoundComponent::SoundIndex, std::string> &sounds)
	{
		scene.addEntity("Keyboard default control")
			.addComponent<ControllableComponent>()
			.addComponent<SoundComponent>(sounds)
			.addComponent<KeyboardComponent>();
		scene.addEntity("Keyboard second control")
			.addComponent<ControllableComponent>()
			.addComponent<SoundComponent>(sounds)
			.addComponent<KeyboardComponent>(ControllableComponent::Layout::KEYBOARD_1);
		for (int i = 0; i < 4; i++) {
			scene.addEntity("Gamepad controller")
				.addComponent<ControllableComponent>()
				.addComponent<SoundComponent>(sounds)
				.addComponent<GamepadComponent>(i);
		}
	}

	void Runner::loadScenes()
	{
		gameState._loadedScenes[GameState::SceneID::MainMenuScene] = loadMainMenuScene();
		gameState._loadedScenes[GameState::SceneID::SettingsScene] = loadSettingsMenuScene();
		gameState._loadedScenes[GameState::SceneID::PauseMenuScene] = loadPauseMenuScene();
		gameState._loadedScenes[GameState::SceneID::TitleScreenScene] = loadTitleScreenScene();
		gameState._loadedScenes[GameState::SceneID::CreditScene] = loadCreditScene();
		gameState._loadedScenes[GameState::SceneID::SplashScreen] = loadSplashScreenScene();
		gameState._loadedScenes[GameState::SceneID::LobbyScene] = loadLobbyScene();
		gameState._loadedScenes[GameState::SceneID::ResumeLobbyScene] = loadResumeLobbyScene();
		gameState._loadedScenes[GameState::SceneID::HowToPlayScene] = loadHowToPlayScene();
	}

	int Runner::run()
	{
		std::srand(std::time(nullptr));
		WAL::Wal wal;
		Runner::addSystems(wal);
		Runner::enableRaylib(wal);
		Runner::loadScenes();
		wal.changeScene(Runner::gameState._loadedScenes[GameState::SceneID::SplashScreen]);
		wal.run<GameState>(Runner::updateState, Runner::gameState);
		return 0;
	}
}