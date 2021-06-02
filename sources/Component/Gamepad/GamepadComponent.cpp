//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "GamepadComponent.hpp"

namespace BBM
{
	GamepadComponent::GamepadComponent(WAL::Entity &entity)
		: WAL::Component(entity), _ID(0)
	{}

		GamepadComponent::GamepadComponent(WAL::Entity &entity, int ID)
		: WAL::Component(entity), _ID(ID)
	{}

	WAL::Component *GamepadComponent::clone(WAL::Entity &entity) const
	{
		return new GamepadComponent(entity, _ID);
	}

	GamepadComponent &GamepadComponent::setID(int ID)
	{
		this->_ID = ID;
		return *this;
	}

	int GamepadComponent::getID() const
	{
		return this->_ID;
	}

} // namespace BMM
