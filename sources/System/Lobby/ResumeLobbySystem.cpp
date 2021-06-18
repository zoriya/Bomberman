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
#include <algorithm>
#include <Runner/Runner.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <Component/Gamepad/GamepadComponent.hpp>
#include "Component/IAControllable/IAControllableComponent.hpp"
#include <Component/Position/PositionComponent.hpp>
#include <Component/Renderer/Drawable3DComponent.hpp>
#include <Map/Map.hpp>
#include <Component/BombHolder/BombHolderComponent.hpp>
#include <Parser/ParserYaml.hpp>
#include <Drawables/2D/Text.hpp>
#include "Component/Color/ColorComponent.hpp"
#include "Component/Stat/StatComponent.hpp"
#include "Component/Bonus/PlayerBonusComponent.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	std::array<std::string, 4> ResumeLobbySystem::_colors = {
			"blue",
			"red",
			"green",
			"yellow"
	};

	std::array<RAY::Color, 4> ResumeLobbySystem::_rayColors = {
			BLUE,
			RED,
			GREEN,
			YELLOW
	};

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
				if (controller.select) {
					if (std::any_of(this->getView().begin(), this->getView().end(), [&controller](WAL::ViewEntity<ResumeLobbyComponent, Drawable2DComponent> &view) {
						return view.get<ResumeLobbyComponent>().layout == controller.layout;
					}))
						return;
					lobby.ready = true;
					lobby.lastInput = lastTick;
					lobby.layout = controller.layout;
					controller.select = false;
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
		auto &view = this->_wal.getScene()->view<TagComponent<"PlayButton">, Drawable2DComponent>();
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
		});
	}

	void ResumeLobbySystem::addController(WAL::Entity &player, ControllableComponent::Layout layout)
	{
		switch (layout) {
			case ControllableComponent::KEYBOARD_0:
			case ControllableComponent::KEYBOARD_1:
				player.addComponent<KeyboardComponent>(layout);
				break;
			case ControllableComponent::GAMEPAD_0:
				player.addComponent<GamepadComponent>(0);
				break;
			case ControllableComponent::GAMEPAD_1:
				player.addComponent<GamepadComponent>(1);
				break;
			case ControllableComponent::GAMEPAD_2:
				player.addComponent<GamepadComponent>(2);
				break;
			case ControllableComponent::GAMEPAD_3:
				player.addComponent<GamepadComponent>(3);
				break;
			case ControllableComponent::AI:
				player.addComponent<IAControllableComponent>("./assets/ai_scripts/john.lua");
				break;
			default:
				throw std::runtime_error("Invalid controller for a player.");
		}
	}

	void ResumeLobbySystem::resumeToGame(WAL::Wal &wal)
	{
		auto scene = Runner::gameState._loadedScenes[GameState::SceneID::GameScene];
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
			addController(player, lobby.layout);
			std::string texturePath = "assets/player/ui/" + _colors[lobby.color] + ".png";
			int x = (countPlayer % 2 == 0) ? 1920 - 10 - 320 : 10;
			int y = (countPlayer % 3 != 0) ? 1080 - 10 - 248 : 10;
			scene->addEntity("player color tile")
					.addComponent<PositionComponent>(x, y - 2, 0)
					.addComponent<Drawable2DComponent, RAY2D::Rectangle>(x, y, 320, 248, _rayColors[lobby.color]);
			scene->addEntity("player ui tile")
					.addComponent<PositionComponent>(x, y, 0)
					.addComponent<Drawable2DComponent, RAY::Texture>(texturePath);
			scene->addEntity("player hide fireup")
					.addComponent<PositionComponent>(x + 220, y + 35, 0)
					.addComponent<Drawable2DComponent, RAY2D::Text>("", 20, x, y, WHITE)
					.addComponent<StatComponent>([&player](Drawable2DComponent &drawble) {
						const BombHolderComponent *bonus = player.tryGetComponent<BombHolderComponent>();

						if (!bonus)
							return;
						RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(drawble.drawable.get());
						if (!text)
							return;
						text->setText(std::to_string(static_cast<int>(bonus->explosionRadius)));
					});
			scene->addEntity("player hide bombup")
					.addComponent<PositionComponent>(x + 220, y + 77, 0)
					.addComponent<Drawable2DComponent, RAY2D::Text>("", 20, x, y, WHITE)
					.addComponent<StatComponent>([&player](Drawable2DComponent &drawble) {
						const BombHolderComponent *bonus = player.tryGetComponent<BombHolderComponent>();

						if (!bonus)
							return;
						RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(drawble.drawable.get());
						if (!text)
							return;
						text->setText(std::to_string(bonus->bombCount) + " / " + std::to_string(bonus->maxBombCount));
					});
			scene->addEntity("player hide speedup")
					.addComponent<PositionComponent>(x + 220, y + 122, 0)
					.addComponent<Drawable2DComponent, RAY2D::Text>("", 20, x, y, WHITE)
					.addComponent<StatComponent>([&player](Drawable2DComponent &drawble) {
						auto *speed = player.tryGetComponent<SpeedComponent>();

						if (!speed)
							return;
						RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(drawble.drawable.get());
						if (!text)
							return;
						text->setText(std::to_string(static_cast<int>(speed->speed * 100)));
					});
			scene->addEntity("player hide wall")
					.addComponent<PositionComponent>(x + 220, y + 161, 0)
					.addComponent<Drawable2DComponent, RAY2D::Text>("", 20, x, y, WHITE)
					.addComponent<StatComponent>([&player](Drawable2DComponent &drawble) {
						const PlayerBonusComponent *bonus = player.tryGetComponent<PlayerBonusComponent>();

						if (!bonus)
							return;
						RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(drawble.drawable.get());
						if (!text)
							return;
						text->setText(bonus->isNoClipOn ? "YES" : "NO");
					});
			countPlayer++;
		}
		Runner::gameState.nextScene = BBM::GameState::SceneID::GameScene;
		wal.getSystem<ResumeLobbySystem>().unloadLobbyFromResume();
	}

	void ResumeLobbySystem::unloadLobbyFromResume()
	{
		for (auto &entity : this->getView()) {
			entity->scheduleDeletion();
		}
	}
}