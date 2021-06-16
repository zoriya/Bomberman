//
// Created by hbenjamin on 15/06/2021.
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
	int Runner::addedPlayer = 0;

	std::shared_ptr<WAL::Scene> Runner::loadResumeLobbyScene()
	{
		static const std::map<SoundComponent::SoundIndex, std::string> sounds = {
				{SoundComponent::JUMP, "assets/sounds/click.ogg"}
		};
		auto scene = std::make_shared<WAL::Scene>();

		addMenuControl(*scene);
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
													if (Runner::gameState.currentScene != GameState::ResumeLobbyScene
														|| !LobbySystem::playersAreReady(*wal.getScene()))
														return;
													LobbySystem::resumeToGame(wal);
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
		scene->addEntity("camera")
				.addComponent<PositionComponent>(8, 20, 7)
				.addComponent<CameraComponent>(Vector3f(8, 0, 8));
		play.getComponent<OnClickComponent>().setButtonLinks(nullptr, &back, &back, nullptr);
		back.getComponent<OnClickComponent>().setButtonLinks(&play, nullptr, nullptr, &play);
		return scene;
	}
}