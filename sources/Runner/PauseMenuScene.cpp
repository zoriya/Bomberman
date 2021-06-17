
#include <memory>
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
#include <Parser/ParserYaml.hpp>
#include "Component/Music/MusicComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Keyboard/KeyboardComponent.hpp"
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
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
		auto scene = std::make_shared<WAL::Scene>();

		addMenuControl(*scene, sounds);
		scene->addEntity("Control entity")
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
		auto &save = scene->addEntity("save & quit button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 240, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_save.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_save.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_save_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				if (!std::filesystem::exists("save"))
					std::filesystem::create_directories("save");
				ParserYAML::save(Runner::gameState._loadedScenes[GameState::SceneID::GameScene]);
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
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
			.addComponent<PositionComponent>(1920 / 1.55, 1080 - 360, 0)
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
		save.getComponent<OnClickComponent>().setButtonLinks(&play);
		play.getComponent<OnClickComponent>().setButtonLinks(nullptr, &save, nullptr, &settings);
		settings.getComponent<OnClickComponent>().setButtonLinks(nullptr, &save, &play, &exit);
		exit.getComponent<OnClickComponent>().setButtonLinks(nullptr, &save, &settings, nullptr);
		return scene;
	}
}