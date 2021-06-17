//
// Created by Zoe Roux on 6/11/21.
//

#include "System/Event/EventSystem.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "System/Lobby/LobbySystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include "Component/Tag/TagComponent.hpp"
#include <algorithm>
#include <Runner/Runner.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <Component/Gamepad/GamepadComponent.hpp>
#include "Component/IAControllable/IAControllableComponent.hpp"
#include <Component/Position/PositionComponent.hpp>
#include <Component/Renderer/Drawable3DComponent.hpp>
#include <Drawables/2D/Text.hpp>
#include <Drawables/2D/Text.hpp>
#include "Component/Color/ColorComponent.hpp"
#include "Component/Stat/StatComponent.hpp"
#include "Component/Bonus/PlayerBonusComponent.hpp"
#include "Component/BombHolder/BombHolderComponent.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM
{
	std::array<std::string, 4> LobbySystem::_colors = {
		"blue",
		"red",
		"green",
//		"purple", TODO MISSING ICONS
//		"cyan",
		"yellow"
	};

	std::array<RAY::Color, 4> LobbySystem::_rayColors = {
		BLUE,
		RED,
		GREEN,
		// PURPLE,
		// SKYBLUE,
		YELLOW
	};

	LobbySystem::LobbySystem(WAL::Wal &wal)
		: System(wal)
	{}

	void LobbySystem::_nextColor(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity)
	{
		auto &lobby = entity.get<LobbyComponent>();
		if (lobby.color != -1)
			this->_colorTaken[lobby.color] = false;
		do {
			lobby.color++;
			if (lobby.color >= this->_colorTaken.size())
				lobby.color = 0;
		} while (this->_colorTaken[lobby.color]);
		this->_colorTaken[lobby.color] = true;
		entity.get<Drawable2DComponent>().drawable = std::make_shared<RAY::Texture>("assets/player/icons/" + _colors[lobby.color] + ".png");
		lobby.coloredTile.getComponent<Drawable2DComponent>().drawable->setColor(_rayColors[lobby.color]);
	}

	void LobbySystem::onUpdate(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &lobby = entity.get<LobbyComponent>();

		auto lastTick = std::chrono::steady_clock::now();
		if (lastTick - lobby.lastInput < std::chrono::milliseconds(150))
			return;

		if (lobby.layout == ControllableComponent::NONE) {
			for (auto &[_, ctrl] : this->_wal.getScene()->view<ControllableComponent>()) {
				auto &controller = ctrl;
				if (controller.select) {
					if (std::any_of(this->getView().begin(), this->getView().end(), [&controller](WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &view) {
						return view.get<LobbyComponent>().layout == controller.layout;
					}))
						return;
					lobby.lastInput = lastTick;
					lobby.color = -1;
					this->_nextColor(entity);
					lobby.layout = controller.layout;
					controller.select = false;
					return;
				}
			}
		}

		for (auto &[_, controller] : this->_wal.getScene()->view<ControllableComponent>()) {
			if (controller.layout != lobby.layout)
				continue;
			if (controller.select && !lobby.ready) {
				lobby.ready = true;
				lobby.lastInput = lastTick;
				controller.select = false;
				this->_wal.getSystem<MenuControllableSystem>().now = lastTick;
				auto *texture = dynamic_cast<RAY::Texture *>(lobby.readyButton.getComponent<Drawable2DComponent>().drawable.get());
				if (texture)
					texture->use("assets/player/icons/ready.png");
			}
			if (controller.bomb && !lobby.ready) {
				lobby.lastInput = lastTick;
				this->_nextColor(entity);
			}
		}
	}

	void LobbySystem::addAI()
	{
		for (auto entity : this->getView()) {
			auto &lobby = entity.get<LobbyComponent>();
			if (lobby.layout != ControllableComponent::NONE)
				continue;
			lobby.color = -1;
			this->_nextColor(entity);
			lobby.layout = ControllableComponent::AI;
			lobby.ready = true;
			auto *texture = dynamic_cast<RAY::Texture *>(lobby.readyButton.getComponent<Drawable2DComponent>().drawable.get());
			if (texture)
				texture->use("assets/player/icons/ai.png");
			return;
		}
	}

	void LobbySystem::removeAI()
	{
		std::optional<WAL::ViewEntity<LobbyComponent, Drawable2DComponent>> last;
		for (auto &entity : this->getView()) {
			auto &lobby = entity.get<LobbyComponent>();
			if (lobby.layout == ControllableComponent::AI)
				last.emplace(entity);
		}
		if (!last)
			return;
		auto &entity = *last;
		auto &lobby = entity.get<LobbyComponent>();
		auto &drawable = entity.get<Drawable2DComponent>();
		this->_colorTaken[lobby.color] = false;
		lobby.color = -1;
		lobby.layout = ControllableComponent::NONE;
		lobby.ready = false;
		drawable.drawable = std::make_shared<RAY::Texture>("assets/player/icons/none.png");
		lobby.coloredTile.getComponent<Drawable2DComponent>().drawable->setColor(RAY::Color(0, 0, 0, 0));
		auto *texture = dynamic_cast<RAY::Texture *>(lobby.readyButton.getComponent<Drawable2DComponent>().drawable.get());
		if (texture)
			texture->unload();
	}

	void LobbySystem::onSelfUpdate(std::chrono::nanoseconds dtime)
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

	bool LobbySystem::playersAreReady(WAL::Scene &scene)
	{
		auto &lobby = scene.view<LobbyComponent>();
		return std::all_of(lobby.begin(), lobby.end(), [](WAL::ViewEntity<LobbyComponent> &entity) {
			auto &lobbyPlayer = entity.get<LobbyComponent>();
			return lobbyPlayer.ready || lobbyPlayer.layout == ControllableComponent::NONE;
		});
	}

	void LobbySystem::_addController(WAL::Entity &player, ControllableComponent::Layout layout)
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

	void LobbySystem::switchToGame(WAL::Wal &wal)
	{
		auto scene = Runner::loadGameScene();
		int mapWidth = 16;
		int mapHeight = 16;
		int playerCount = 0;

		for (auto &[_, lobby] : wal.getScene()->view<LobbyComponent>()) {
			if (lobby.layout == ControllableComponent::NONE)
				continue;
			auto &player = Runner::createPlayer(*scene);
			_addController(player, lobby.layout);
			player.getComponent<PositionComponent>().position = Vector3f(mapWidth * (playerCount % 2),
																		 (Runner::hasHeights ? 1.01 : 0),
																		 mapHeight * (!(playerCount % 3)));
			auto *model = dynamic_cast<RAY3D::Model *>(player.getComponent<Drawable3DComponent>().drawable.get());
			model->setTextureToMaterial(MAP_DIFFUSE, "assets/player/textures/" + _colors[lobby.color] + ".png");
			std::string texturePath = "assets/player/ui/" + _colors[lobby.color] + ".png";
			int x = (playerCount % 2 == 0) ? 1920 - 10 - 320 : 10;
			int y = (playerCount % 3 != 0) ? 1080 - 10 - 248 : 10;
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
					text->setText(std::to_string(bonus->explosionRadius));
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
					const ControllableComponent *bonus = player.tryGetComponent<ControllableComponent>();

					if (!bonus)
						return;
					RAY2D::Text *text = dynamic_cast<RAY2D::Text *>(drawble.drawable.get());
					if (!text)
						return;
					text->setText(std::to_string(static_cast<int>(bonus->speed * 100)));
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
			playerCount++;
		}
		Runner::gameState._loadedScenes[GameState::SceneID::GameScene] = scene;
		Runner::gameState.nextScene = BBM::GameState::SceneID::GameScene;
		wal.getSystem<LobbySystem>().unloadLobby();
	}

	void LobbySystem::unloadLobby()
	{
		this->_colorTaken.fill(false);
		for (auto &[_, lobby, drawable] : this->getView()) {
			lobby.layout = ControllableComponent::NONE;
			lobby.ready = false;
			lobby.color = -1;
			drawable.drawable = std::make_shared<RAY::Texture>("assets/player/icons/none.png");
			lobby.coloredTile.getComponent<Drawable2DComponent>().drawable->setColor(RAY::Color(0, 0, 0, 0));
			auto *texture = dynamic_cast<RAY::Texture *>(lobby.readyButton.getComponent<Drawable2DComponent>().drawable.get());
			if (texture)
				texture->unload();
		}
	}
}