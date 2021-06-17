
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

		for (auto &[entity, score, drawable]: gameScene.view<ScoreComponent, Drawable3DComponent>())
			players.push_back(entity);
		std::sort(players.begin(), players.end(), [](WAL::Entity &entityA, WAL::Entity &entityB) {
			return entityA.getComponent<ScoreComponent>().aliveTime > entityB.getComponent<ScoreComponent>().aliveTime;
		});

		for (auto &entity: players) {
			RAY3D::Model *model = dynamic_cast<RAY3D::Model *>(entity.get().getComponent<Drawable3DComponent>().drawable.get());
			std::string path = model->getTextureByMaterial(MAP_DIFFUSE).getResourcePath();
			playersIconPath.push_back(path.replace(path.find("textures"), std::string("textures").size(), "icons"));
		}

		addMenuControl(*scene, sounds);
		scene->addEntity("Audio ressources")
			.addComponent<MusicComponent>("assets/musics/music_result.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");
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
		scene->addEntity("back to main menu")
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
		return scene;
	}
}