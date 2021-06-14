//
// Created by Tom Augier on 2021-05-20.
//

#include "GravityComponent.hpp"

namespace BBM
{
	GravityComponent::GravityComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	WAL::Component *GravityComponent::clone(WAL::Entity &entity) const
	{
		return new GravityComponent(entity);
	}
}