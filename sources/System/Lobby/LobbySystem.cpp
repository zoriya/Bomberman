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

	//void LobbySystem::updateEntityConnectedUser(WAL::Entity &entity)
	//{
	//	RAY::Texture *texture = dynamic_cast<RAY::Texture *>(entity.getComponent<Drawable2DComponent>().drawable.get());
	//	texture->use("assets/player/icons/blue.png");
	//}
}