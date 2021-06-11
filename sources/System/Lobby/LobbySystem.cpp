#include <Component/Animation/AnimationsComponent.hpp>
#include <System/Event/EventSystem.hpp>
#include "System/Lobby/LobbySystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"

namespace BBM
{
	LobbySystem::LobbySystem(WAL::Wal &wal)
		: System(wal)
	{}

	void LobbySystem::onUpdate(WAL::ViewEntity<LobbyComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &lobby = entity.get<LobbyComponent>();
		if (lobby.layout == ControllableComponent::NONE) {
			for (auto &[_, controller] : this->_wal.getScene()->view<ControllableComponent>()) {
				if (controller.jump) {
					lobby.layout = controller.layout;
					return;
				}
			}
		}
		for (auto &[_, controller] : this->_wal.getScene()->view<ControllableComponent>()) {
			if (controller.layout == lobby.layout && controller.jump) {
				lobby.ready = !lobby.ready;
				if (lobby.ready) {
				}
			}
		}
	}
}