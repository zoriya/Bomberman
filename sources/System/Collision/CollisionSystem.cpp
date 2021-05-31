//
// Created by Louis Auzuret on 5/20/21
//

#include "Component/Movable/MovableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Collision/CollisionComponent.hpp"
#include "System/Collision/CollisionSystem.hpp"

namespace BBM
{
	CollisionSystem::CollisionSystem(WAL::Wal &wal)
	: WAL::System({typeid(PositionComponent), typeid(CollisionComponent)}), _wal(wal)
	{

	}
	void CollisionSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &posA = entity.getComponent<PositionComponent>();
		auto &col = entity.getComponent<CollisionComponent>();
		Vector3f position = posA.position;
		if (entity.hasComponent(typeid(MovableComponent)))
			position += entity.getComponent<MovableComponent>()._velocity;
		Vector3f minA = Vector3f::min(position, position + col.bound);
		Vector3f maxA = Vector3f::max(position, position + col.bound);
		for (auto &other : _wal.scene->getEntities()) {
			if (&other == &entity)
				continue;
			if (!other.hasComponent(typeid(CollisionComponent)) ||
				!other.hasComponent(typeid(PositionComponent)))
				continue;
			auto colB = entity.getComponent<CollisionComponent>().bound;
			auto posB = other.getComponent<PositionComponent>().position;
			Vector3f minB = Vector3f::min(posB, posB + colB);
			Vector3f maxB = Vector3f::max(posB, posB + colB);
			if ((minA.x <= maxB.x && maxA.x >= minB.x) &&
        		(minA.y <= maxB.y && maxA.y >= minB.y) &&
        		(minA.z <= maxB.z && maxA.z >= minB.z))
				col.onCollide(entity, other);
		}
	}
}