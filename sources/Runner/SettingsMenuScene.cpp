
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
#include "System/Renderer/RenderSystem.hpp"

namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
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
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/plain_menu_background.png");
		scene->addEntity("logo")
			.addComponent<PositionComponent>(1920 / 3, 180, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/logo_small.png");
		auto &music = scene->addEntity("music text")
			.addComponent<PositionComponent>(1920 / 2.5, 1080 - 540, 0)
			.addComponent<Drawable2DComponent, RAY2D::Text>(false, "Music Volume", 70, RAY::Vector2(), BLACK)
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
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/buttons/button_plus.png")
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
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/buttons/button_minus.png")
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
			.addComponent<Drawable2DComponent, RAY2D::Text>(false, "Sound Volume", 70, RAY::Vector2(), BLACK)
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
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/buttons/button_plus.png")
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
			.addComponent<Drawable2DComponent, RAY::Texture>(false, "assets/buttons/button_minus.png")
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
			.addComponent<Drawable2DComponent, RAY2D::Text>(false, "Debug Mode: Off", 70, RAY::Vector2(), BLACK)
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
}