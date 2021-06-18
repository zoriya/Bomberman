
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
#include "Component/Button/ButtonComponent.hpp"
#include "Component/Music/MusicComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Component/Sound/SoundComponent.hpp"
#include "Drawables/Texture.hpp"
#include "Drawables/2D/Text.hpp"
#include "Component/Score/ScoreComponent.hpp"
#include "Model/Model.hpp"
#include "System/Lobby/LobbySystem.hpp"
#include "Component/Tag/TagComponent.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;
namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	std::shared_ptr<WAL::Scene> Runner::loadScoreScene(WAL::Scene &gameScene)
	{
		auto scene = std::make_shared<WAL::Scene>();
		std::vector<std::string> playersIconPath;
		std::vector<std::reference_wrapper<WAL::Entity>> players;
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
		static const std::vector<RAY::Color> tilesColor = {
			GOLD, GRAY, BROWN, PURPLE
		};
		static const std::vector<std::string> rankName = {
			"1st", "2nd", "3rd", "4th"
		};

		for (WAL::Entity &entity : gameScene.view<ScoreComponent, Drawable3DComponent>())
			players.emplace_back(entity);
		std::sort(players.begin(), players.end(), [](WAL::Entity &entityA, WAL::Entity &entityB) {
			return entityA.getComponent<ScoreComponent>().aliveTime > entityB.getComponent<ScoreComponent>().aliveTime;
		});

		int playerID = 0;
		for (auto &entity : players) {
			auto *model = dynamic_cast<RAY3D::Model *>(entity.get().getComponent<Drawable3DComponent>().drawable.get());
			std::string path = model->getTextureByMaterial(MAP_DIFFUSE).getResourcePath();
			playersIconPath.push_back(path.replace(path.find("textures"), std::string("textures").size(), "icons"));

			auto &newPlayer = scene->addEntity("add");
			newPlayer.addComponent<LobbyComponent>(playerID++, newPlayer, newPlayer);
			auto &lobby = newPlayer.getComponent<LobbyComponent>();
			lobby.layout = entity.get().getComponent<ControllableComponent>().layout;

			auto start = path.find_last_of('/') + 1;
			std::string color = path.substr(start, path.find_last_of('.') - start);
			auto iterator = std::find(LobbySystem::colors.begin(), LobbySystem::colors.end(), color);
			lobby.color = static_cast<int>(iterator - LobbySystem::colors.begin());
		}

		addMenuControl(*scene, sounds);
		scene->addEntity("Audio ressources")
			.addComponent<MusicComponent>("assets/musics/music_result.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/backgrounds/score.png");
		scene->addEntity("white background")
			.addComponent<PositionComponent>(200, 100, 0)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(Vector2f(), Vector2f(1525, 550), RAY::Color(BLACK).setA(150));
		scene->addEntity("scene title text")
			.addComponent<PositionComponent>(1920 / 3.25, 100, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("GAME OVER", 120, RAY::Vector2(), ORANGE);
		scene->addEntity("scene title text")
			.addComponent<PositionComponent>(1920 / 2.37, 250, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("CONGRATS", 50, RAY::Vector2(), ORANGE);
		for (int i = 0; i < players.size(); i++) {
			auto &playerTile = scene->addEntity("player tile")
				.addComponent<PositionComponent>(224 * (i + 1) + 200 * i, 1080 / 2.5, 0)
				.addComponent<Drawable2DComponent, RAY2D::Rectangle>(RAY::Vector2(224 * (i + 1) + 200 * i, 1080 / 3),
				                                                     RAY::Vector2(200, 200), tilesColor[i]);
			auto &playerRank = scene->addEntity("player rank name")
				.addComponent<PositionComponent>(224 * (i + 1) + 200 * i, 1080 / 2.75, 0)
				.addComponent<Drawable2DComponent, RAY2D::Text>(rankName[i], 30,
				                                                RAY::Vector2(224 * (i + 1) + 200 * i, 1080 / 3),
				                                                tilesColor[i]);
			auto &player = scene->addEntity("player")
				.addComponent<PositionComponent>(224 * (i + 1) + 200 * i, 1080 / 2.5, 0)
				.addComponent<Drawable2DComponent, RAY::Texture>(playersIconPath[i]);
		}
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
				LobbySystem::switchToGame(wal);
			});
		auto &back = scene->addEntity("back to main menu")
			.addComponent<PositionComponent>(10, 1080 - 85, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_back.png")
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &) {
				gameState.nextScene = BBM::GameState::SceneID::MainMenuScene;
			})
			.addComponent<OnIdleComponent>([](WAL::Entity &entity, WAL::Wal &) {
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back.png");
			})
			.addComponent<OnHoverComponent>([](WAL::Entity &entity, WAL::Wal &) {
				RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());

				texture->use("assets/buttons/button_back_hovered.png");
			});
		back.getComponent<OnClickComponent>().setButtonLinks(&play, nullptr, nullptr, &play);
		play.getComponent<OnClickComponent>().setButtonLinks(nullptr, &back, &back);
		return scene;
	}
}