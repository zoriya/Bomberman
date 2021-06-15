
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

		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/plain_menu_background.png");

		scene->addEntity("Control entity")
			.addComponent<ControllableComponent>()
			.addComponent<KeyboardComponent>()
			.addComponent<MusicComponent>("assets/musics/music_title.ogg")
			.addComponent<SoundComponent>(sounds);

		auto &raylibLogo = scene->addEntity("raylib logo")
			.addComponent<PositionComponent>(1920 / 4, 1080 / 1.75, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/raylib.png");
		auto &raylibText = scene->addEntity("raylib text")
			.addComponent<PositionComponent>(1920 / 4, 1080 / 2, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>(false, "Powered by:", 35, RAY::Vector2(), BLACK);
		auto &otherRepoText = scene->addEntity("other repo text")
			.addComponent<PositionComponent>(1920 / 4, 1080 / 4, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>(false, "Many Thanks to:", 35, RAY::Vector2(), BLACK);
		auto &BriansRepo = scene->addEntity("thx brian")
			.addComponent<PositionComponent>(1920 / 3.5, 1080 / 3.5, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>(false, "Brian Guitteny (and his team)", 35, RAY::Vector2(), BLACK);
		auto &team = scene->addEntity("team")
			.addComponent<PositionComponent>(1920 / 1.5, 1080 / 3.5, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>(false, "Team:\n Zoe Roux\n Clément Le Bihan\n Arthur Jamet\n Louis Auzuret\n Benjamin Henry\n Tom Augier", 35, RAY::Vector2(), BLACK);
		auto &back = scene->addEntity("back to menu")
			.addComponent<PositionComponent>(10, 1080 - 85, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/buttons/button_back.png")
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

}