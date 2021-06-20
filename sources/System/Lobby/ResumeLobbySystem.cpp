//
// Created by Zoe Roux on 6/11/21.
//

#include "System/Event/EventSystem.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "System/Lobby/ResumeLobbySystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Speed/SpeedComponent.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include "Component/Tag/TagComponent.hpp"
#include <Runner/Runner.hpp>
#include <Component/Position/PositionComponent.hpp>
#include <Component/Renderer/Drawable3DComponent.hpp>
#include <Component/BombHolder/BombHolderComponent.hpp>
#include <Parser/ParserYaml.hpp>
#include "Component/Color/ColorComponent.hpp"
#include "System/Lobby/LobbySystem.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	ResumeLobbySystem::ResumeLobbySystem(WAL::Wal &wal)
			: System(wal)
	{}

	void ResumeLobbySystem::onUpdate(WAL::ViewEntity<ResumeLobbyComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &lobby = entity.get<ResumeLobbyComponent>();

		auto lastTick = std::chrono::steady_clock::now();
		if (lastTick - lobby.lastInput < std::chrono::milliseconds(150))
			return;

		if (lobby.layout == ControllableComponent::NONE) {
			for (auto &[_, ctrl] : this->_wal.getScene()->view<ControllableComponent>()) {
				auto &controller = ctrl;
				if (controller.bomb) {
					if (std::any_of(this->getView().begin(), this->getView().end(), [&controller](WAL::ViewEntity<ResumeLobbyComponent, Drawable2DComponent> &view) {
						return view.get<ResumeLobbyComponent>().layout == controller.layout;
					}))
						return;
					lobby.ready = true;
					lobby.lastInput = lastTick;
					lobby.layout = controller.layout;
					controller.bomb = false;
					this->_wal.getSystem<MenuControllableSystem>().now = lastTick;
					auto *texture = dynamic_cast<RAY::Texture *>(lobby.readyButton.getComponent<Drawable2DComponent>().drawable.get());
					if (texture)
						texture->use("assets/player/icons/ready.png");
					return;
				}
			}
		}
	}

	void ResumeLobbySystem::onSelfUpdate(std::chrono::nanoseconds dtime)
	{
		auto &view = this->_wal.getScene()->view<TagComponent<ResumeButton>, Drawable2DComponent>();
		if (view.size() == 0)
			return;
		auto *texture = dynamic_cast<RAY::Texture *>(view.front().get<Drawable2DComponent>().drawable.get());
		if (!texture)
			return;
		if (playersAreReady(*this->_wal.getScene()))
			texture->setColor(WHITE);
		else
			texture->setColor(GRAY);
	}

	bool ResumeLobbySystem::playersAreReady(WAL::Scene &scene)
	{
		auto &lobby = scene.view<ResumeLobbyComponent>();
		return std::all_of(lobby.begin(), lobby.end(), [](WAL::ViewEntity<ResumeLobbyComponent> &entity) {
			auto &lobbyPlayer = entity.get<ResumeLobbyComponent>();
			return lobbyPlayer.ready && lobbyPlayer.layout != ControllableComponent::NONE;
		});	}

	void ResumeLobbySystem::resumeToGame(WAL::Wal &wal)
	{
		auto scene = Runner::gameState.loadedScenes[GameState::SceneID::GameScene];
		int countPlayer = 0;

		for (auto &[_, lobby] : wal.getScene()->view<ResumeLobbyComponent>()) {
			if (lobby.layout == ControllableComponent::NONE)
				continue;
			auto &player = Runner::createPlayer(*scene);
			player.setName(ParserYAML::playersInfos[countPlayer].name);
			auto *position = player.tryGetComponent<PositionComponent>();
			auto *bombHolder = player.tryGetComponent<BombHolderComponent>();
			auto *model = player.tryGetComponent<Drawable3DComponent>();
			auto *speed = player.tryGetComponent<SpeedComponent>();
			if (position && bombHolder && model && speed) {
				dynamic_cast<RAY3D::Model *>(model->drawable.get())->setTextureToMaterial(MAP_DIFFUSE,
				                                                                          ParserYAML::playersInfos[countPlayer].asset);
				position->position = ParserYAML::playersInfos[countPlayer].position;
				bombHolder->explosionRadius = ParserYAML::playersInfos[countPlayer].explosionRange;
				bombHolder->maxBombCount = ParserYAML::playersInfos[countPlayer].maxBombCount;
				speed->speed = ParserYAML::playersInfos[countPlayer].speed;
			}
			LobbySystem::addController(player, lobby.layout);
			LobbySystem::createTile(scene, player, lobby.playerColor, countPlayer);
			countPlayer++;
		}
		Runner::gameState.nextScene = BBM::GameState::SceneID::GameScene;
		wal.getSystem<ResumeLobbySystem>().unloadLobbyFromResume();
		ParserYAML::playersInfos.clear();
	}

	void ResumeLobbySystem::unloadLobbyFromResume()
	{
		for (auto &entity : this->getView()) {
			entity->scheduleDeletion();
		}
	}
}