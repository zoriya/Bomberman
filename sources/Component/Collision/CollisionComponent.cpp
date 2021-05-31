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
	: WAL::Component(entity), onCollide(callback), bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> callback, float boundSize)
	: WAL::Component(entity), onCollide(callback), bound({boundSize, boundSize, boundSize})
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback, Vector3f bound)
	: WAL::Component(entity), onCollide(callback), bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> callback, float boundSize)
	: WAL::Component(entity), onCollide(callback), bound({boundSize, boundSize, boundSize})
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, Vector3f bound)
	: WAL::Component(entity), onCollide(), bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, float boundSize)
	: WAL::Component(entity), onCollide(), bound({boundSize, boundSize, boundSize})
	{ }
}