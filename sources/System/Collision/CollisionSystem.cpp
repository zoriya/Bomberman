//
// Created by Louis Auzuret on 5/20/21
//

#include "Component/Movable/MovableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Collision/CollisionComponent.hpp"
#include "System/Collision/CollisionSystem.hpp"
#include "Scene/Scene.hpp"

namespace BBM
{
	CollisionSystem::CollisionSystem(WAL::Wal &wal)
		: System(wal)
	{ }

	bool CollisionSystem::collide(Vector3f minA, Vector3f maxA, Vector3f minB, Vector3f maxB)
	{
		bool overlapX = (minA.x <= maxB.x && maxA.x >= minB.x) || (minB.x <= maxA.x && maxB.x >= minA.x);
		bool overlapY = (minA.y <= maxB.y && maxA.y >= minB.y) || (minB.y <= maxA.y && maxB.y >= minA.y);
		bool overlapZ = (minA.z <= maxB.z && maxA.z >= minB.z) || (minB.z <= maxA.z && maxB.z >= minA.z);

		return (overlapX && overlapY && overlapZ);
	}

	void CollisionSystem::onFixedUpdate(WAL::ViewEntity<PositionComponent, CollisionComponent> &entity)
	{
		auto &posA = entity.get<PositionComponent>();
		auto &col = entity.get<CollisionComponent>();
		Vector3f position = posA.position;
		if (auto *movable = entity->tryGetComponent<MovableComponent>())
			position += movable->getVelocity();
		Vector3f minA = Vector3f::min(position, position + col.bound);
		Vector3f maxA = Vector3f::max(position, position + col.bound);
		for (auto &[other, posB, colB] : this->getView()) {
			if (other.getUid() == entity->getUid())
				continue;
			Vector3f minB = Vector3f::min(posB.position, posB.position + colB.bound);
			Vector3f maxB = Vector3f::max(posB.position, posB.position + colB.bound);
			if (collide(minA, maxA, minB, maxB)) {
				col.onCollide(entity, other);
				colB.onCollided(entity, other);
			}
		}
	}
}