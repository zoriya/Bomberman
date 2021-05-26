//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//

#include "ColliderComponent.hpp"

namespace BBM
{
	ColliderComponent::ColliderComponent(WAL::Entity &entity)
		: Component(entity)
	{}

	ColliderComponent::ColliderComponent(WAL::Entity &entity, std::function<void (const WAL::Entity &, WAL::Entity &)> callback)
		: Component(entity),
		onCollide(callback)
	{}

	WAL::Component *ColliderComponent::clone(WAL::Entity &entity) const
	{
		return new ColliderComponent(entity);
	}
} // namespace WAL