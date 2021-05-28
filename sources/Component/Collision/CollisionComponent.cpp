//
// Created by Louis Auzuret on 2021-05-20.
//

#include "Entity/Entity.hpp"
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

    CollisionComponent::CollisionComponent(WAL::Entity &entity, std::function<void (WAL::Entity &, WAL::Entity &)> callback)
    : WAL::Component(entity), onCollide(callback)
    {

    }

    CollisionComponent::CollisionComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, WAL::Entity &> callback)
    : WAL::Component(entity), onCollide(callback)
    {

    }
}