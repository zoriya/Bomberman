//
// Created by Zoe Roux on 2021-06-14.
//

#include <Wal.hpp>
#include "System/Movable/MovableSystem.hpp"
#include <Model/Model.hpp>
#include <Drawables/2D/Rectangle.hpp>
#include <Drawables/2D/Text.hpp>
#include <TraceLog.hpp>
#include "Component/Button/ButtonComponent.hpp"
#include "Component/Renderer/CameraComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Runner.hpp"
#include "Models/GameState.hpp"
#include <Component/Animator/AnimatorComponent.hpp>
#include <Component/Tag/TagComponent.hpp>
#include <Drawables/Texture.hpp>
#include "System/Sound/PlayerSoundManagerSystem.hpp"
#include "System/Music/MusicSystem.hpp"
#include "System/Lobby/LobbySystem.hpp"
#include "Component/Lobby/LobbyComponent.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	std::shared_ptr<WAL::Scene> Runner::loadLobbyScene()
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
		scene->addEntity("lobby text")
			.addComponent<PositionComponent>(1920 / 2.75, 100, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Get Ready", 120, RAY::Vector2(), ORANGE);
		auto &play = scene->addEntity("play button")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_new_game.png")
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				texture->use("assets/buttons/button_new_game.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				texture->use("assets/buttons/button_new_game_hovered.png");
			})
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				if (Runner::gameState.currentScene != GameState::LobbyScene
					|| !LobbySystem::playersAreReady(*wal.getScene()))
					return;
				LobbySystem::switchToGame(wal);
			})
			.addComponent<TagComponent<"PlayButton">>();
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
		auto &howToPlay = scene->addEntity("to to play")
			.addComponent<PositionComponent>(1920 - 10 - 75, 1080 - 85, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_htp.png")
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::HowToPlayScene;
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_htp.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

			 texture->use("assets/buttons/button_htp_hovered.png");
			});
		auto &lavaOption = scene->addEntity("lava option text")
			.addComponent<PositionComponent>(1920 / 6, 1.85 * 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Lava: Off", 70, RAY::Vector2(), BLACK)
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				if (text->getString().find("Off") != std::string::npos) {
					text->setText("Lava: On");
					//do
				} else {
					text->setText("Lava: Off");
					//do
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

		auto &heightOption = scene->addEntity("Height option text")
			.addComponent<PositionComponent>(1920 / 6, 2.1 * 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("2nd Level: Off", 70, RAY::Vector2(), BLACK)
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				auto *text = dynamic_cast<RAY2D::Text *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				if (text->getString().find("Off") != std::string::npos) {
					text->setText("2nd Level: On");
					Runner::hasHeights = true;
				} else {
					text->setText("2nd Level: Off");
					Runner::hasHeights = false;
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

		auto &aiMore = scene->addEntity("AI+")
			.addComponent<PositionComponent>(1920 / 1.75, 1.85 * 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/cpu_add.png")
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				wal.getSystem<LobbySystem>().addAI();
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				texture->use("assets/buttons/cpu_add.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				texture->use("assets/buttons/cpu_add_hovered.png");
			});

		auto &aiLess = scene->addEntity("AI-")
			.addComponent<PositionComponent>(1920 / 1.75, 2.10 * 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/cpu_remove.png")
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &wal)
			{
				wal.getSystem<LobbySystem>().removeAI();
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				texture->use("assets/buttons/cpu_remove.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				auto *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
				texture->use("assets/buttons/cpu_remove_hovered.png");
			});

		for (int i = 0; i < 4; i++) {
			auto &playerTile = scene->addEntity("player tile")
				.addComponent<PositionComponent>(224 * (i + 1) + 200 * i, 1080 / 3, 0)
				.addComponent<Drawable2DComponent, RAY2D::Rectangle>(RAY::Vector2(224 * (i + 1) + 200 * i, 1080 / 3), RAY::Vector2(200, 200), RAY::Color(0, 0, 0, 0));
			auto &player = scene->addEntity("player")
				.addComponent<PositionComponent>(224 * (i + 1) + 200 * i, 1080 / 3, 0)
				.addComponent<Drawable2DComponent, RAY::Texture>("assets/player/icons/none.png");
			auto &ready = scene->addEntity("ready")
				.addComponent<PositionComponent>(224 * (i + 1) + 200 * i, 1080 / 3, 0)
				// todo check why it does this | hacky way to fix ready texture
				.addComponent<Drawable2DComponent, RAY::Texture>("");
			player.addComponent<LobbyComponent>(i, ready, playerTile);
		}
		scene->addEntity("camera")
			.addComponent<PositionComponent>(8, 20, 7)
			.addComponent<CameraComponent>(Vector3f(8, 0, 8));
		play.getComponent<OnClickComponent>().setButtonLinks(&lavaOption, &back, &back, &howToPlay);
		howToPlay.getComponent<OnClickComponent>().setButtonLinks(&play, nullptr, &play);
		back.getComponent<OnClickComponent>().setButtonLinks(&play, nullptr, nullptr, &play);
		lavaOption.getComponent<OnClickComponent>().setButtonLinks(nullptr, &heightOption, nullptr, &aiMore);
		heightOption.getComponent<OnClickComponent>().setButtonLinks(&lavaOption, &play, nullptr, &aiLess);
		aiMore.getComponent<OnClickComponent>().setButtonLinks(nullptr, &aiLess, &lavaOption, nullptr);
		aiLess.getComponent<OnClickComponent>().setButtonLinks(&aiMore, &play, &heightOption, nullptr);
		return scene;
	}
}