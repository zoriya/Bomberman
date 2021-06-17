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

	CollisionComponent::CollidedAxis operator|(CollisionComponent::CollidedAxis first,
		CollisionComponent::CollidedAxis second)
	{
		return static_cast<CollisionComponent::CollidedAxis>(static_cast<int>(first) | static_cast<int>(second));
	}

	CollisionComponent::CollidedAxis &operator|=(CollisionComponent::CollidedAxis &self,
		CollisionComponent::CollidedAxis other)
	{
		int &selfI = reinterpret_cast<int &>(self);
		int otherI = static_cast<int>(other);

		selfI |= otherI;
		return reinterpret_cast<CollisionComponent::CollidedAxis &>(selfI);
	}
}