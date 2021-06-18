//
// Created by hbenjamin on 6/18/21.
//

#include "ResumeLobbyComponent.hpp"

namespace BBM
{
	ResumeLobbyComponent::ResumeLobbyComponent(WAL::Entity &entity, int playerNumber, WAL::Entity &button, WAL::Entity &tile, int pColor)
			: WAL::Component(entity),
			  playerID(playerNumber),
			  readyButton(button),
			  coloredTile(tile),
			  playerColor(pColor)
	{}

	WAL::Component *ResumeLobbyComponent::clone(WAL::Entity &entity) const
	{
		return new ResumeLobbyComponent(entity, this->playerID, this->readyButton, this->coloredTile, this->playerColor);
	}
}