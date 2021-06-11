//
// Created by hbenjamin on 09/06/2021.
//

#include "PlayerBonusComponent.hpp"

namespace BBM {
	PlayerBonusComponent::PlayerBonusComponent(WAL::Entity &entity)
			: WAL::Component(entity)
	{}

	WAL::Component *PlayerBonusComponent::clone(WAL::Entity &entity) const
	{
		return new PlayerBonusComponent(entity);
	}
}
