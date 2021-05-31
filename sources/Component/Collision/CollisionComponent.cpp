//
// Created by Louis Auzuret on 2021-05-20.
//

#include "lib/wal/sources/Entity/Entity.hpp"
#include "sources/Component/Collision/CollisionComponent.hpp"


namespace BBM 
{
	CollisionComponent::CollisionComponent(WAL::Entity &entity)
	: WAL::Component(entity)
	{ }

	WAL::Component *CollisionComponent::clone(WAL::Entity &entity) const
	{
		return new CollisionComponent(entity);
	}

	CollisionComponent::CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> callback, Vector3f bound)
	: WAL::Component(entity), onCollide(callback), _boundX(bound.x), _boundY(bound.y), _boundZ(bound.z)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> callback, float boundSize)
	: WAL::Component(entity), onCollide(callback), _boundX(boundSize), _boundY(boundSize), _boundZ(boundSize)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback, Vector3f bound)
	: WAL::Component(entity), onCollide(callback), _boundX(bound.x), _boundY(bound.y), _boundZ(bound.z)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback, float boundSize)
	: WAL::Component(entity), onCollide(callback), _boundX(boundSize), _boundY(boundSize), _boundZ(boundSize)
	{ }

	float CollisionComponent::getBoundX(void) const
	{
		return _boundX;
	}

	float CollisionComponent::getBoundY(void) const
	{
		return _boundY;
	}

	float CollisionComponent::getBoundZ(void) const
	{
		return _boundZ;
	}

	void CollisionComponent::setBoundX(float value)
	{
		_boundX = value;
	}

	void CollisionComponent::setBoundY(float value)
	{
		_boundY = value;
	}

	void CollisionComponent::setBoundZ(float value)
	{
		_boundZ = value;
	}
}