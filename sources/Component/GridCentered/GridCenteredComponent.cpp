//
// Created by Zoe Roux on 5/24/21.
//

#include "GridCenteredComponent.hpp"

namespace BBM
{
	GridCenteredComponent::GridCenteredComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	WAL::Component *GridCenteredComponent::clone(WAL::Entity &entity) const
	{
		return new GridCenteredComponent(entity);
	}
}