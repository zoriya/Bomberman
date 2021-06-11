//
// Created by Zoe Roux on 6/11/21.
//

#include "LobbyComponent.hpp"

namespace BBM
{
	LobbyComponent::LobbyComponent(WAL::Entity &entity, int playerID)
		: WAL::Component(entity),
		playerID(playerID)
	{}

	WAL::Component *LobbyComponent::clone(WAL::Entity &entity) const
	{
		return new LobbyComponent(entity, this->playerID);
	}
}