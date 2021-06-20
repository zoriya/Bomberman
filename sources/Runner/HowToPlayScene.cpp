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
	std::shared_ptr<WAL::Scene> Runner::loadHowToPlayScene()
	{
		auto scene = std::make_shared<WAL::Scene>();
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
			{SoundComponent::BOMB, "assets/sounds/click.ogg"}
		};

		addMenuControl(*scene, sounds);
		scene->addEntity("Control entity")
			.addComponent<MusicComponent>("assets/musics/music_player_select.ogg")
			.addComponent<SoundComponent>(sounds);
		scene->addEntity("background")
			.addComponent<PositionComponent>()
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/backgrounds/menu.png");
		scene->addEntity("white background")
			.addComponent<PositionComponent>(200, 100, 0)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(Vector2f(), Vector2f(1525, 600), RAY::Color(WHITE).setA(150));
		scene->addEntity("scene title text")
			.addComponent<PositionComponent>(1920 / 3, 100, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("How To Play?", 120, RAY::Vector2(), ORANGE);
		scene->addEntity("select text")
			.addComponent<PositionComponent>(1920 / 8, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Select/Drop Bomb:", 60, RAY::Vector2(), ORANGE);
		scene->addEntity("select")
			.addComponent<PositionComponent>(1920 / 7, 1080 / 2.5, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Space/Left CTRL/A Button", 35, RAY::Vector2(), BLACK);
		scene->addEntity("change skin text")
			.addComponent<PositionComponent>(1920 / 8, 1080 / 2, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Change Skin:", 60, RAY::Vector2(), ORANGE);
		scene->addEntity("change skin")
			.addComponent<PositionComponent>(1920 / 7, 1080 / 1.75, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Left ctrl/Right shift/B Button", 35, RAY::Vector2(), BLACK);
		scene->addEntity("move text")
			.addComponent<PositionComponent>(1920 / 1.75, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Move:", 60, RAY::Vector2(), ORANGE);
		scene->addEntity("move")
			.addComponent<PositionComponent>(1920 / 1.75, 1080 / 2.5, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Q-Z-S-D/Arrow/Joystick", 35, RAY::Vector2(), BLACK);
		scene->addEntity("back text")
			.addComponent<PositionComponent>(1920 / 1.75, 1080 / 2, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Back/Pause:", 60, RAY::Vector2(), ORANGE);
		scene->addEntity("back")
			.addComponent<PositionComponent>(1920 / 1.75, 1080 / 1.75, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>("Esc/Backspace/Controller's Home button:", 35, RAY::Vector2(), BLACK);
		scene->addEntity("back to menu")
			.addComponent<PositionComponent>(10, 1080 - 85, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>("assets/buttons/button_back.png")
			.addComponent<OnClickComponent>([](WAL::Entity &entity, WAL::Wal &)
			{
				gameState.nextScene = BBM::GameState::SceneID::LobbyScene;
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