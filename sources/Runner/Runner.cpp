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
#include <Audio/Music.hpp>
#include <Audio/Sound.hpp>
#include <Drawables/2D/Rectangle.hpp>
#include <TraceLog.hpp>
#include "System/Keyboard/KeyboardSystem.hpp"
#include "System/Controllable/ControllableSystem.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Keyboard/KeyboardComponent.hpp"
#include "System/Gamepad/GamepadSystem.hpp"
#include <System/Collision/CollisionSystem.hpp>
#include "Component/Button/ButtonComponent.hpp"
#include <Component/Movable/MovableComponent.hpp>
#include <Component/Collision/CollisionComponent.hpp>
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Runner.hpp"
#include "Models/GameState.hpp"
#include <Model/ModelAnimations.hpp>
#include <System/Timer/TimerSystem.hpp>
#include <System/BombHolder/BombHolderSystem.hpp>
#include <System/Event/EventSystem.hpp>
#include <System/Health/HealthSystem.hpp>
#include <System/Animator/AnimatorSystem.hpp>
#include <Component/Renderer/Drawable2DComponent.hpp>
#include <Component/Animator/AnimatorComponent.hpp>
#include <Component/Tag/TagComponent.hpp>
#include "Component/Animation/AnimationsComponent.hpp"
#include "System/Animation/AnimationsSystem.hpp"
#include "Component/Shaders/ShaderComponent.hpp"
#include "Map/Map.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include <Drawables/Texture.hpp>
#include "Component/Music/MusicComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
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
		auto &view = engine.getScene()->view<ControllableComponent>();
		// You can change the scene here or update the game state based on entities values.

		// If you want to keep a scene loaded but not running, store it in the state.loadedScenes.
		//      If you don't need the scene anymore, remember to remove it from the loadedScene array.
		if (RAY::Window::getInstance().shouldClose())
			engine.shouldClose = true;
		if (gameState.currentScene == GameState::SceneID::GameScene) {
			for (auto &[_, component]: view) {
				if (component.pause) {
					gameState.nextScene = GameState::SceneID::PauseMenuScene;
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
			.addSystem<MovableSystem>()
			.addSystem<PlayerSoundManagerSystem>()
			.addSystem<MenuSoundManagerSystem>()
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

	std::shared_ptr<WAL::Scene> Runner::loadTitleScreenScene()
	{
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
		auto scene = std::make_shared<WAL::Scene>();
		scene->addEntity("control")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<SoundComponent>(sounds)
			.addComponent<MusicComponent>("assets/musics/music_title.ogg");
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
		scene->addEntity("logo")
			.addComponent<PositionComponent>(320, 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/logo_big.png");
		scene->addEntity("text_prompt")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 130, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Press space", 70, RAY::Vector2(), BLACK)
			.addComponent<OnIdleComponent>()
			.addComponent<OnHoverComponent>()
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			});
		return scene;
	}

	std::shared_ptr<WAL::Scene> Runner::loadMainMenuScene()
	{
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
		auto scene = std::make_shared<WAL::Scene>();

		scene->addEntity("Control entity")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<MusicComponent>("assets/musics/music_title.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
		scene->addEntity("logo")
			.addComponent<PositionComponent>(1920 / 3, 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/logo_small.png");
		auto &play = scene->addEntity("play button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 540, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_new_game.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_new_game.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_new_game_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::GameScene;
			});
		auto &settings = scene->addEntity("settings button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_settings.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_settings.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_settings_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::SettingsScene;
			});
		auto &exit = scene->addEntity("exit button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_exit.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_exit.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_exit_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				wal.shouldClose = true;
			});
		auto &credits = scene->addEntity("credit button")
			.addComponent<PositionComponent>(1920 - 100, 1080 - 30, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Credits", 20, RAY::Vector2(), BLACK)
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				text->setColor(BLACK);
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				text->setColor(ORANGE);
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				gameState.nextScene = BBM::GameState::SceneID::CreditScene;
			});
		play.getComponent<OnClickComponent>().setButtonLinks(nullptr, &settings);
		settings.getComponent<OnClickComponent>().setButtonLinks(&play, &exit);
		exit.getComponent<OnClickComponent>().setButtonLinks(&settings, &credits, nullptr, &credits);
		credits.getComponent<OnClickComponent>().setButtonLinks(&exit, nullptr, &exit);
		return scene;
	}

	std::shared_ptr<WAL::Scene> Runner::loadPauseMenuScene()
	{
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
		auto scene = std::make_shared<WAL::Scene>();

		scene->addEntity("Control entity")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<MusicComponent>("assets/musics/music_player_select.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
		scene->addEntity("pause text")
			.addComponent<PositionComponent>(1920 / 2.5, 180, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("PAUSE", 120, RAY::Vector2(), ORANGE);
		auto &play = scene->addEntity("play button")
			.addComponent<PositionComponent>(1920 / 6.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_back.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::GameScene;
			});
		auto &settings = scene->addEntity("settings button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_settings.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_settings.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_settings_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::SettingsScene;
			});
		auto &exit = scene->addEntity("exit button")
			.addComponent<PositionComponent>(1920 / 1.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_exit.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_exit.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_exit_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			});
		//needed material
		//music
		play.getComponent<OnClickComponent>().setButtonLinks(nullptr, nullptr, nullptr, &settings);
		settings.getComponent<OnClickComponent>().setButtonLinks(nullptr, nullptr, &play, &exit);
		exit.getComponent<OnClickComponent>().setButtonLinks(nullptr, nullptr, &settings, nullptr);
		return scene;
	}

	std::shared_ptr<WAL::Scene> Runner::loadSettingsMenuScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};

		scene->addEntity("Control entity")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<MusicComponent>("assets/musics/music_title.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
		scene->addEntity("logo")
			.addComponent<PositionComponent>(1920 / 3, 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/logo_small.png");
		auto &music = scene->addEntity("music text")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 540, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Music Volume", 70, RAY::Vector2(), BLACK)
			.addComponent<OnClickComponent>()
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				entity.getComponent<Drawable2DComponent>().drawable->setColor(BLACK);
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				entity.getComponent<Drawable2DComponent>().drawable->setColor(ORANGE);
			});

		auto &musicUp = scene->addEntity("music up button")
			.addComponent<PositionComponent>(1920 / 1.5, 1080 - 540, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_plus.png")
			.addComponent<MusicComponent>("assets/musics/music_title.ogg")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_plus.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto &component = entity.getComponent<MusicComponent>();

				component.turnUpVolume();
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_plus_hovered.png");
			});

		auto &musicDown = scene->addEntity("music down button")
			.addComponent<PositionComponent>(1920 / 3, 1080 - 540, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_minus.png")
			.addComponent<MusicComponent>("assets/musics/music_title.ogg")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_minus.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto &component = entity.getComponent<MusicComponent>();

				component.turnDownVolume();
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_minus_hovered.png");
			});

		auto &sound = scene->addEntity("sound text")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Sound Volume", 70, RAY::Vector2(), BLACK)
			.addComponent<OnClickComponent>()
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				entity.getComponent<Drawable2DComponent>().drawable->setColor(BLACK);
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				entity.getComponent<Drawable2DComponent>().drawable->setColor(ORANGE);
			});

		auto &soundUp = scene->addEntity("sound up button")
			.addComponent<PositionComponent>(1920 / 1.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_plus.png")
			.addComponent<SoundComponent>(sounds)
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto &component = entity.getComponent<SoundComponent>();

				component.turnUpVolume();
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_plus.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_plus_hovered.png");
			});

		auto &soundDown = scene->addEntity("sound down button")
			.addComponent<PositionComponent>(1920 / 3, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_minus.png")
			.addComponent<SoundComponent>(sounds)
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_minus.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto &component = entity.getComponent<SoundComponent>();

				component.turnDownVolume();
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_minus_hovered.png");
			});

		auto &debug = scene->addEntity("debug text")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 180, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Debug Mode: Off", 70, RAY::Vector2(), BLACK)
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				if (text->getString().find("Off") != std::string::npos) {
					text->setText("Debug Mode: On");
					wal.getSystem<RenderSystem>().setDebug(true);
				} else {
					text->setText("Debug Mode: Off");
					wal.getSystem<RenderSystem>().setDebug(false);
				}
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				entity.getComponent<Drawable2DComponent>().drawable->setColor(BLACK);
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				entity.getComponent<Drawable2DComponent>().drawable->setColor(ORANGE);
			});
		auto &back = scene->addEntity("back to menu")
			.addComponent<PositionComponent>(10, 1080 - 85, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_back.png")
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back_hovered.png");
			});
		//needed material
		//music
		//sound

		music.getComponent<OnClickComponent>().setButtonLinks(nullptr, &sound, &musicDown, &musicUp);
		musicDown.getComponent<OnClickComponent>().setButtonLinks(&debug, &sound, nullptr, &music);
		musicUp.getComponent<OnClickComponent>().setButtonLinks(&debug, &sound, &music);
		sound.getComponent<OnClickComponent>().setButtonLinks(&music, &debug, &soundDown, &soundUp);
		soundDown.getComponent<OnClickComponent>().setButtonLinks(&music, &debug, nullptr, &sound);
		soundUp.getComponent<OnClickComponent>().setButtonLinks(&music, &debug, &sound);
		debug.getComponent<OnClickComponent>().setButtonLinks(&sound, &back, &back);
		back.getComponent<OnClickComponent>().setButtonLinks(&debug, nullptr, nullptr, &debug);
		return scene;
	}

	std::shared_ptr<WAL::Scene> Runner::loadGameScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		scene->addEntity("control")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>();
		std::map<SoundComponent::SoundIndex, std::string> soundPath ={
		    {SoundComponent::JUMP, "assets/sounds/jump.wav"},
		    {SoundComponent::MOVE, "assets/sounds/move.ogg"},
		    {SoundComponent::BOMB, "assets/sounds/bomb_drop.ogg"},
		    //{SoundComponent::DEATH, "assets/sounds/death.ogg"}
		};
		scene->addEntity("player")
			.addComponent<PositionComponent>()
			.addComponent<Drawable3DComponent, RAY3D::Model>("assets/player/player.iqm", std::make_pair(MAP_DIFFUSE, "assets/player/blue.png"))
			.addComponent<ControllableComponent>()
			.addComponent<AnimatorComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<ShaderComponentModel>("assets/shaders/glsl330/predator.fs")
			.addComponent<TagComponent<Blowable>>()
			//.addComponent<GamepadComponent>(0)
			.addComponent<AnimationsComponent>(RAY::ModelAnimations("assets/player/player.iqm"), 3)
			.addComponent<CollisionComponent>(BBM::Vector3f{0.25, 0, 0.25}, BBM::Vector3f{.75, 2, .75})
			.addComponent<MovableComponent>()
			.addComponent<SoundComponent>(soundPath)
			.addComponent<MusicComponent>("assets/musics/music_battle.ogg")
			.addComponent<BombHolderComponent>()
			.addComponent<HealthComponent>(1, [](WAL::Entity &entity) {
				auto &animation = entity.getComponent<AnimationsComponent>();
				animation.setAnimIndex(5);
			});
		scene->addEntity("camera")
			.addComponent<PositionComponent>(8, 20, 7)
			.addComponent<CameraComponent>(Vector3f(8, 0, 8));
		MapGenerator::loadMap(16, 16, MapGenerator::createMap(16, 16), scene);

		return scene;
	}

	std::shared_ptr<WAL::Scene> Runner::loadCreditScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};

		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");

		scene->addEntity("Control entity")
		/*scene->addEntity("cube")
			.addComponent<PositionComponent>(5, 0, 5)
			.addComponent<ShaderComponentDrawable2D>("assets/shaders/glsl330/grayscale.fs")
			//.addComponent<Drawable3DComponent, RAY3D::Cube>(Vector3f(-5, 0, -5), Vector3f(3, 3, 3), RED)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(BBM::Vector2f{200,200}, BBM::Vector2f{200, 200}, RED)
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<CollisionComponent>(WAL::Callback<WAL::Entity &, const WAL::Entity &>(), &MapGenerator::wallCollide, 3); */
			.addComponent<MusicComponent>("assets/musics/music_title.ogg")
			.addComponent<SoundComponent>(sounds);

		auto &raylibLogo = scene->addEntity("raylib logo")
			.addComponent<PositionComponent>(1920 / 4, 1080 / 1.75, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/raylib.png");
		auto &raylibText = scene->addEntity("raylib text")
			.addComponent<PositionComponent>(1920 / 4, 1080 / 2, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Powered by:", 35, RAY::Vector2(), BLACK);
		auto &otherRepoText = scene->addEntity("other repo text")
			.addComponent<PositionComponent>(1920 / 4, 1080 / 4, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Many Thanks to:", 35, RAY::Vector2(), BLACK);
		auto &BriansRepo = scene->addEntity("thx brian")
			.addComponent<PositionComponent>(1920 / 3.5, 1080 / 3.5, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Brian Guitteny (and his team)", 35, RAY::Vector2(), BLACK);
		auto &team = scene->addEntity("team")
			.addComponent<PositionComponent>(1920 / 1.5, 1080 / 3.5, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Team:\n Zoe Roux\n Clément Le Bihan\n Arthur Jamet\n Louis Auzuret\n Benjamin Henry\n Tom Augier", 35, RAY::Vector2(), BLACK);
		auto &back = scene->addEntity("back to menu")
			.addComponent<PositionComponent>(10, 1080 - 85, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_back.png")
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back_hovered.png");
			});
		return scene;
	}

	void Runner::loadScenes()
	{
		gameState._loadedScenes[GameState::SceneID::MainMenuScene] = loadMainMenuScene();
		gameState._loadedScenes[GameState::SceneID::GameScene] = loadGameScene();
		gameState._loadedScenes[GameState::SceneID::SettingsScene] = loadSettingsMenuScene();
		gameState._loadedScenes[GameState::SceneID::PauseMenuScene] = loadPauseMenuScene();
		gameState._loadedScenes[GameState::SceneID::TitleScreenScene] = loadTitleScreenScene();
		gameState._loadedScenes[GameState::SceneID::CreditScene] = loadCreditScene();
	}

	int Runner::run()
	{
		std::srand(std::time(nullptr));
		WAL::Wal wal;
		Runner::addSystems(wal);
		Runner::enableRaylib(wal);
		Runner::loadScenes();
		wal.changeScene(Runner::gameState._loadedScenes[GameState::SceneID::TitleScreenScene]);

		try {
			wal.run<GameState>(Runner::updateState, Runner::gameState);
			return 0;
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
			return 1;
		}
	}
}