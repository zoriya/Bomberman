#include <Component/Animation/AnimationsComponent.hpp>
#include "System/Lobby/LobbySystem.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	LobbySystem::LobbySystem(WAL::Wal &wal)
		: System(wal)
	{}

	void LobbySystem::onSelfUpdate()
	{
	}
}