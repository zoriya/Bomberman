//
// Created by Zoe Roux on 6/11/21.
//

#include "LobbyComponent.hpp"

namespace BBM
{
	LobbyComponent::LobbyComponent(WAL::Entity &entity, int playerID, WAL::Entity &readyButton, WAL::Entity &coloredTile)
		: WAL::Component(entity),
		playerID(playerID),
		readyButton(readyButton),
		coloredTile(coloredTile)
	{}

	WAL::Component *LobbyComponent::clone(WAL::Entity &entity) const
	{
		return new LobbyComponent(entity, this->playerID, this->readyButton, this->coloredTile);
	}
}