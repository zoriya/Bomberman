//
// Created by Louis Auzuret on 2021-05-20.
//

#include "Component/Collision/CollisionComponent.hpp"


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
	: WAL::Component(entity), onCollide(callback), _bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> callback, float boundSize)
	: WAL::Component(entity), onCollide(callback), _bound({boundSize, boundSize, boundSize})
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback, Vector3f bound)
	: WAL::Component(entity), onCollide(callback), _bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback, float boundSize)
	: WAL::Component(entity), onCollide(callback), _bound({boundSize, boundSize, boundSize})
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, Vector3f bound)
	: WAL::Component(entity), onCollide(), _bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, float boundSize)
	: WAL::Component(entity), onCollide(), _bound({boundSize, boundSize, boundSize})
	{ }

	Vector3f CollisionComponent::getBounds(void) const
	{
		return _bound;
	}

	float CollisionComponent::getBoundX(void) const
	{
		return _bound.x;
	}

	float CollisionComponent::getBoundY(void) const
	{
		return _bound.y;
	}

	float CollisionComponent::getBoundZ(void) const
	{
		return _bound.z;
	}

	void CollisionComponent::setBoundX(float value)
	{
		_bound.x = value;
	}

	void CollisionComponent::setBoundY(float value)
	{
		_bound.y = value;
	}

	void CollisionComponent::setBoundZ(float value)
	{
		_bound.z = value;
	}
}