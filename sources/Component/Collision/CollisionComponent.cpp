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
    CollisionComponent::CollisionComponent(WAL::Entity &entity, int boundSize)
    : WAL::Component(entity), _boundX(boundSize), _boundY(boundSize), _boundZ(boundSize)
    { }
    CollisionComponent::CollisionComponent(WAL::Entity &entity, int boundX, int boundY, int boundZ)
    : WAL::Component(entity)
    { }
	int CollisionComponent::getBoundX(void) const
    {
        return _boundX;
    }
	int CollisionComponent::getBoundY(void) const
    {
        return _boundY;
    }
	int CollisionComponent::getBoundZ(void) const
    {
        return _boundZ;
    }
	void CollisionComponent::setBoundX(int value)
    {
        _boundX = value;
    }
	void CollisionComponent::setBoundY(int value)
    {
        _boundY = value;
    }
	void CollisionComponent::setBoundZ(int value)
    {
        _boundZ = value;
    }
	WAL::Component *CollisionComponent::clone(WAL::Entity &entity) const
    {
        return new CollisionComponent(entity);
    }
}