//
// Created by hbenjamin on 07/06/2021.
//

#include "BombAnimatorComponent.hpp"

namespace BBM
{
	BombAnimatorComponent::BombAnimatorComponent(WAL::Entity &entity)
			: WAL::Component(entity)
	{}

	WAL::Component *BombAnimatorComponent::clone(WAL::Entity &entity) const
	{
		return new BombAnimatorComponent(entity);
	}
}