
#include <memory>
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
#include <Parser/ParserYaml.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include "Component/Music/MusicComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Keyboard/KeyboardComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Button/ButtonComponent.hpp"
#include "Drawables/2D/Text.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	std::shared_ptr<WAL::Scene> Runner::loadMainMenuScene()
	{
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
		auto scene = std::make_shared<WAL::Scene>();

		addMenuControl(*scene, sounds);
		scene->addEntity("Control entity")
			.addComponent<MusicComponent>("assets/musics/music_title.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/backgrounds/menu.png");
		scene->addEntity("logo")
			.addComponent<PositionComponent>(1920 / 3, 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/logo_small.png");
		auto &play = scene->addEntity("play button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 650, 0)
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
				gameState.nextScene = BBM::GameState::SceneID::LobbyScene;
			});
		auto &resume = scene->addEntity("resume button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 540, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_resume_game.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
		   {
			   RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

			   texture->use("assets/buttons/button_resume_game.png");
		   })
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_resume_game_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::ResumeLobbyScene;
				auto gameScene = Runner::loadGameScene();
				try {
					ParserYAML::load(gameScene);
				} catch (std::exception const &err) {
					std::cout << err.what() << std::endl;
					gameScene->addEntity("Error message parser")
							.addComponent<PositionComponent>(1920 / 5, 2 * 1080 / 4.25, 0)
							.addComponent<TimerComponent>(3s, [](WAL::Entity &myEntity, WAL::Wal &wal) {
								myEntity.scheduleDeletion();
							})
							.addComponent<Drawable2DComponent, RAY2D::Text>(err.what(), 50, RAY::Vector2(), RED);
					gameState.nextScene = BBM::GameState::SceneID::GameScene;
					return;
				}
				Runner::gameState._loadedScenes[GameState::SceneID::GameScene] = gameScene;
			});
		auto &settings = scene->addEntity("settings button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 430, 0)
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
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 320, 0)
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
		play.getComponent<OnClickComponent>().setButtonLinks(nullptr, &resume);
		resume.getComponent<OnClickComponent>().setButtonLinks(&play, &settings);
		settings.getComponent<OnClickComponent>().setButtonLinks(&resume, &exit);
		exit.getComponent<OnClickComponent>().setButtonLinks(&settings, &credits, nullptr, &credits);
		credits.getComponent<OnClickComponent>().setButtonLinks(&exit, nullptr, &exit);
		return scene;
	}
}