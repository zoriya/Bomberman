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

	CollisionComponent::CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> onCollide, std::function<void (WAL::Entity &, const WAL::Entity &)> onCollided, Vector3f bound)
	: WAL::Component(entity), _onCollide(onCollide), _onCollided(onCollided), bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, const WAL::Entity &)> onCollide, std::function<void (WAL::Entity &, const WAL::Entity &)> onCollided, float boundSize)
	: WAL::Component(entity), _onCollide(onCollide), _onCollided(onCollided), bound({boundSize, boundSize, boundSize})
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollide, WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollided, Vector3f bound)
	: WAL::Component(entity), _onCollide(onCollide), _onCollided(onCollided), bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollide, WAL::Callback<WAL::Entity &, const WAL::Entity &> onCollided, float boundSize)
	: WAL::Component(entity), _onCollide(onCollide), _onCollided(onCollided), bound({boundSize, boundSize, boundSize})
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, Vector3f bound)
	: WAL::Component(entity), _onCollide(), _onCollided(), bound(bound)
	{ }

	CollisionComponent::CollisionComponent(WAL::Entity &entity, float boundSize)
	: WAL::Component(entity), _onCollide(), _onCollided(), bound({boundSize, boundSize, boundSize})
	{ }

	const WAL::Callback<WAL::Entity &, const WAL::Entity &> &CollisionComponent::getOnCollide(void) const
	{
		return _onCollide;
	}

	const WAL::Callback<WAL::Entity &, const WAL::Entity &> &CollisionComponent::getOnCollided(void) const
	{
		return _onCollided;
	}

}