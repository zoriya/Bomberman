//
// Created by Louis Auzuret on 2021-05-20.
//

#include "Component/Collision/CollisionComponent.hpp"

namespace BBM
{
	CollisionComponent::CollisionComponent(WAL::Entity &entity)
		: WAL::Component(entity)
	{}

	WAL::Component *CollisionComponent::clone(WAL::Entity &entity) const
	{
		return new CollisionComponent(entity);
	}

	CollisionComponent::CollisionComponent(WAL::Entity &entity,
	                                       const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollide,
	                                       const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollided,
	                                       Vector3f positionOffset,
	                                       Vector3f bound)
		: WAL::Component(entity),
		onCollide(onCollide),
		onCollided(onCollided),
		bound(bound),
		positionOffset(positionOffset)
	{}

	CollisionComponent::CollisionComponent(WAL::Entity &entity,
	                                       const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollide,
	                                       const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollided,
	                                       float positionOffset,
	                                       float boundSize)
		: WAL::Component(entity),
		onCollide(onCollide),
		onCollided(onCollided),
		bound({boundSize, boundSize, boundSize}),
		positionOffset({positionOffset, positionOffset, positionOffset})
	{}

	CollisionComponent::CollisionComponent(WAL::Entity &entity, Vector3f positionOffset, Vector3f bound)
		: WAL::Component(entity),
		onCollide(),
		onCollided(),
		bound(bound),
		positionOffset(positionOffset)
	{}

	CollisionComponent::CollisionComponent(WAL::Entity &entity, float positionOffset, float boundSize)
		: WAL::Component(entity),
		onCollide(),
		onCollided(),
		bound({boundSize, boundSize, boundSize}),
		positionOffset({positionOffset, positionOffset, positionOffset})
	{}
}