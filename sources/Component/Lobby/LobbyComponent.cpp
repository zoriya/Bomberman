//
// Created by Zoe Roux on 6/11/21.
//

#include "LobbyComponent.hpp"

namespace BBM
{
	LobbyComponent::LobbyComponent(WAL::Entity &entity, int playerID, WAL::Entity &readyButton)
		: WAL::Component(entity),
		playerID(playerID),
		readyButton(readyButton)
	{}

	WAL::Component *LobbyComponent::clone(WAL::Entity &entity) const
	{
		return new LobbyComponent(entity, this->playerID, this->readyButton);
	}
}