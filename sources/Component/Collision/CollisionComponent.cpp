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
	                                       const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollideCallback,
	                                       const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollidedCallback,
	                                       Vector3f positionOffsetVector,
	                                       Vector3f boundVector)
		: WAL::Component(entity),
		onCollide(onCollideCallback),
		onCollided(onCollidedCallback),
		bound(boundVector),
		positionOffset(positionOffsetVector)
	{}

	CollisionComponent::CollisionComponent(WAL::Entity &entity,
	                                       const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollideCallback,
	                                       const WAL::Callback<WAL::Entity &, const WAL::Entity &, CollidedAxis> &onCollidedCallback,
	                                       float positionOffsetFloat,
	                                       float boundSize)
		: WAL::Component(entity),
		onCollide(onCollideCallback),
		onCollided(onCollidedCallback),
		bound({boundSize, boundSize, boundSize}),
		positionOffset({positionOffsetFloat, positionOffsetFloat, positionOffsetFloat})
	{}

	CollisionComponent::CollisionComponent(WAL::Entity &entity, Vector3f positionOffsetVector, Vector3f boundVector)
		: WAL::Component(entity),
		onCollide(),
		onCollided(),
		bound(boundVector),
		positionOffset(positionOffsetVector)
	{}

	CollisionComponent::CollisionComponent(WAL::Entity &entity, float positionOffsetFloat, float boundSize)
		: WAL::Component(entity),
		onCollide(),
		onCollided(),
		bound({boundSize, boundSize, boundSize}),
		positionOffset({positionOffsetFloat, positionOffsetFloat, positionOffsetFloat})
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