
#include <memory>
#include <Wal.hpp>
#include "Runner.hpp"
#include <map>
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
	std::shared_ptr<WAL::Scene> Runner::loadCreditScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};

		addMenuControl(*scene, sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/plain_menu_background.png");

		scene->addEntity("Control entity")
			.addComponent<MusicComponent>("assets/musics/music_title.ogg")
			.addComponent<SoundComponent>(sounds);

		auto &raylibLogo = scene->addEntity("raylib logo")
			.addComponent<PositionComponent>(1920 / 3.5 - 200, 1080 / 1.75, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/raylib.png");
		auto &epitechLogo = scene->addEntity("epitech logo")
			.addComponent<PositionComponent>(1920 / 1.5 - 200, 1080 / 1.5, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/epitech.png");
		auto &raylibText = scene->addEntity("raylib text")
			.addComponent<PositionComponent>(1920 / 4 - 200, 1080 / 2, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Powered by:", 35, RAY::Vector2(), BLACK);
		auto &otherRepoText = scene->addEntity("other repo text")
			.addComponent<PositionComponent>(1920 / 4 - 200, 1080 / 4, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Many Thanks to:", 35, RAY::Vector2(), BLACK);
		auto &BriansRepo = scene->addEntity("thx brian")
			.addComponent<PositionComponent>(1920 / 3.5 - 200, 1080 / 3.25, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Brian Guitteny (and his team)\nAssets used by their permission", 35, RAY::Vector2(), BLACK);
		auto &team = scene->addEntity("team")
			.addComponent<PositionComponent>(1920 / 1.5 - 200, 1080 / 4, 0)
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
		scene->addEntity("racoon")
			.addComponent<PositionComponent>(1920 / 1.17 - 200, 1080 / 4, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/credit/rac.png");
		scene->addEntity("arthi")
			.addComponent<PositionComponent>(1920 / 1.17 - 200, 1080 / 2.75, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/credit/art.png");
		scene->addEntity("eternal")
			.addComponent<PositionComponent>(1920 / 1.17 - 200, 1080 / 2.1, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/credit/ete.png");
		scene->addEntity("octopus")
			.addComponent<PositionComponent>(1920 / 1.13 - 140, 1080 / 4 + 70, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/credit/oct.png");
		scene->addEntity("bluub")
			.addComponent<PositionComponent>(1920 / 1.13 - 140, 1080 / 2.75 + 70, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/credit/blu.png");
		scene->addEntity("true")
			.addComponent<PositionComponent>(1920 / 1.13 - 140, 1080 / 2.1 + 70, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/credit/tru.png");
		return scene;
	}

}