//
// Created by Zoe Roux on 6/11/21.
//

#include "LobbyComponent.hpp"

namespace BBM
{
	LobbyComponent::LobbyComponent(WAL::Entity &entity, int playerNumber, WAL::Entity &button, WAL::Entity &tile)
		: WAL::Component(entity),
		playerID(playerNumber),
		readyButton(button),
		coloredTile(tile)
	{}

	WAL::Component *LobbyComponent::clone(WAL::Entity &entity) const
	{
		return new LobbyComponent(entity, this->playerID, this->readyButton, this->coloredTile);
	}
}