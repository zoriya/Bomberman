//
// Created by Zoe Roux on 6/11/21.
//

#include "Component/Animation/AnimationsComponent.hpp"
#include "System/Event/EventSystem.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "System/Lobby/LobbySystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "System/MenuControllable/MenuControllableSystem.hpp"
#include "Component/Tag/TagComponent.hpp"
#include <algorithm>

namespace BBM
{
	LobbySystem::LobbySystem(WAL::Wal &wal)
		: System(wal)
	{}

	void LobbySystem::onUpdate(WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &lobby = entity.get<LobbyComponent>();

		auto lastTick = std::chrono::steady_clock::now();
		if (lastTick - lobby.lastInput < std::chrono::milliseconds(150))
			return;

		if (lobby.layout == ControllableComponent::NONE) {
			for (auto &[_, controller] : this->_wal.getScene()->view<ControllableComponent>()) {
				if (controller.jump) {
					if (std::any_of(this->getView().begin(), this->getView().end(), [&controller](WAL::ViewEntity<LobbyComponent, Drawable2DComponent> &view) {
						return view.get<LobbyComponent>().layout == controller.layout;
					}))
						return;
					lobby.lastInput = lastTick;
					lobby.layout = controller.layout;
					controller.jump = false;
					entity.get<Drawable2DComponent>().drawable = std::make_shared<RAY::Texture>("assets/player/icons/blue.png");
					return;
				}
			}
		}

		for (auto &[_, controller] : this->_wal.getScene()->view<ControllableComponent>()) {
			if (controller.layout == lobby.layout && controller.jump && !lobby.ready) {
				lobby.ready = true;
				lobby.lastInput = lastTick;
				controller.jump = false;
				this->_wal.getSystem<MenuControllableSystem>().now = lastTick;
				auto *texture = dynamic_cast<RAY::Texture *>(lobby.readyButton.getComponent<Drawable2DComponent>().drawable.get());
				if (texture)
					texture->use("assets/player/icons/ready.png");
			}
		}
	}



	void LobbySystem::onSelfUpdate()
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
}