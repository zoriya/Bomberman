
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
#include <System/Renderer/CameraSystem.hpp>
#include "Component/Health/HealthComponent.hpp"
#include "Component/Timer/TimerComponent.hpp"
#include "Component/Tag/TagComponent.hpp"
#include <Parser/ParserYaml.hpp>
#include "Component/Music/MusicComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Button/ButtonComponent.hpp"
#include "Drawables/2D/Text.hpp"
#include <filesystem>

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	std::shared_ptr<WAL::Scene> Runner::loadPauseMenuScene()
	{
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::BOMB, "assets/sounds/click.ogg"}
		};
		auto scene = std::make_shared<WAL::Scene>();

		addMenuControl(*scene, sounds);
		scene->addEntity("Control entity")
			.addComponent<MusicComponent>("assets/musics/music_player_select.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/backgrounds/pause.png");
			scene->addEntity("white background")
			.addComponent<PositionComponent>(1920 / 2.5 - 20, 180, 0)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(Vector2f(), Vector2f(450, 110), RAY::Color(BLACK).setA(150));
		scene->addEntity("pause text")
			.addComponent<PositionComponent>(1920 / 2.5, 180, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("PAUSE", 120, RAY::Vector2(), ORANGE);
		auto &play = scene->addEntity("play button")
			.addComponent<PositionComponent>(1920 / 6.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_back.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &, WAL::Wal &)
			{
				auto &gameScene = gameState.loadedScenes[BBM::GameState::SceneID::GameScene];

				for (WAL::Entity &entity : gameScene->view<TagComponent<RestartTimer>>())
					entity.scheduleDeletion();

				for (auto &[entity, controller, _] : gameScene->view<ControllableComponent, HealthComponent>()) {
					controller.disabled = true;
					controller.pause = false;
					controller.bomb = false;
				}
				for (auto &[_, timer] : gameScene->view<TimerComponent>())
					timer.disabled = true;
				gameScene->scheduleNewEntity("Restart timer")
					.addComponent<TimerComponent>(std::chrono::seconds(3), [gameScene](WAL::Entity &entity, WAL::Wal &) {
						for (auto &view : gameScene->view<ControllableComponent, HealthComponent>()) {
							if (view.get<HealthComponent>().getHealthPoint() > 0)
								view.get<ControllableComponent>().disabled = false;
						}
						for (auto &view : gameScene->view<TimerComponent>())
							view.get<TimerComponent>().disabled = false;
						entity.scheduleDeletion();
					})
					.addComponent<PositionComponent>(1920 / 2 - 2 * 30, 1080 / 2, 0)
					.addComponent<TagComponent<Timer>>()
					.addComponent<TagComponent<RestartTimer>>()
					.addComponent<Drawable2DComponent, RAY2D::Text>("", 60, RAY::Vector2(), ORANGE);
				gameState.nextScene = BBM::GameState::SceneID::GameScene;
			});
		auto &save = scene->addEntity("save & quit button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 240, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_save.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_save.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_save_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &, WAL::Wal &wal)
			{
				if (!std::filesystem::exists("save"))
					std::filesystem::create_directories("save");
				ParserYAML::save(Runner::gameState.loadedScenes[GameState::SceneID::GameScene]);
				wal.getSystem<CameraSystem>().hasEnded = false;
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			});
		auto &settings = scene->addEntity("settings button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_settings.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_settings.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_settings_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::SettingsScene;
			});
		auto &exit = scene->addEntity("exit button")
			.addComponent<PositionComponent>(1920 / 1.55, 1080 - 360, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_exit.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_exit.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_exit_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &, WAL::Wal &wal)
			{
				wal.getSystem<CameraSystem>().hasEnded = false;
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			});
		save.getComponent<OnClickComponent>().setButtonLinks(&settings);
		play.getComponent<OnClickComponent>().setButtonLinks(nullptr, &save, nullptr, &settings);
		settings.getComponent<OnClickComponent>().setButtonLinks(nullptr, &save, &play, &exit);
		exit.getComponent<OnClickComponent>().setButtonLinks(nullptr, &save, &settings, nullptr);
		return scene;
	}
}