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
	: WAL::System({typeid(PositionComponent), typeid(CollisionComponent)}), _wal(wal)
	{

	}

	bool CollisionSystem::collide(Vector3f minA, Vector3f maxA, Vector3f minB, Vector3f maxB)
	{
		bool overlapX = (minA.x <= maxB.x && maxA.x >= minB.x) || (minB.x <= maxA.x && maxB.x >= minA.x);
		bool overlapY = (minA.y <= maxB.y && maxA.y >= minB.y) || (minB.y <= maxA.y && maxB.y >= minA.y);
		bool overlapZ = (minA.z <= maxB.z && maxA.z >= minB.z) || (minB.z <= maxA.z && maxB.z >= minA.z);

		return (overlapX && overlapY && overlapZ);
	}

	void CollisionSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &posA = entity.getComponent<PositionComponent>();
		auto &col = entity.getComponent<CollisionComponent>();
		Vector3f position = posA.position;
		if (entity.hasComponent(typeid(MovableComponent)))
			position += entity.getComponent<MovableComponent>().getVelocity();
		Vector3f minA = Vector3f::min(position, position + col.bound);
		Vector3f maxA = Vector3f::max(position, position + col.bound);
		for (auto &other : _wal.scene->getEntities()) {
			if (&other == &entity)
				continue;
			if (!other.hasComponent<CollisionComponent>() ||
				!other.hasComponent<PositionComponent>())
				continue;
			auto colB = other.getComponent<CollisionComponent>();
			auto posB = other.getComponent<PositionComponent>().position;
			Vector3f minB = Vector3f::min(posB, posB + colB.bound);
			Vector3f maxB = Vector3f::max(posB, posB + colB.bound);
			if (collide(minA, maxA, minB, maxB)) {
				col.onCollide(entity, other);
				colB.onCollided(entity, other);
			}
		}
	}
}