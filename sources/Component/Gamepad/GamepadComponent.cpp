//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include <Component/Controllable/ControllableComponent.hpp>
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

	void GamepadComponent::onStart()
	{
		auto *controller = this->_entity.tryGetComponent<ControllableComponent>();
		if (!controller)
			return;
		switch (this->_ID) {
		case 0:
			controller->layout = ControllableComponent::GAMEPAD_0;
			break;
		case 1:
			controller->layout = ControllableComponent::GAMEPAD_1;
			break;
		case 2:
			controller->layout = ControllableComponent::GAMEPAD_2;
			break;
		case 3:
			controller->layout = ControllableComponent::GAMEPAD_3;
			break;
		default:
			return;
		}
	}

} // namespace BMM
