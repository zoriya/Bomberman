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
		auto &colA = entity.get<CollisionComponent>();
		Vector3f pointA = posA.position + colA.positionOffset;

		if (auto *movable = entity->tryGetComponent<MovableComponent>())
			pointA += movable->getVelocity();

		Vector3f minA = Vector3f::min(pointA, pointA + colA.bound);
		Vector3f maxA = Vector3f::max(pointA, pointA + colA.bound);

		for (auto &[other, posB, colB] : this->getView()) {
			if (other.getUid() == entity->getUid())
				continue;

			auto pointB = posB.position + colB.positionOffset;

			// TODO if B is also a movable we don't check with it's changing position
			Vector3f minB = Vector3f::min(pointB, pointB + colB.bound);
			Vector3f maxB = Vector3f::max(pointB, pointB + colB.bound);

			if (collide(minA, maxA, minB, maxB)) {
				std::cout << "collided" << std::endl
				<< "minA " << minA << std::endl
				<< "maxA " << maxA << std::endl
				<< "minB " << minB << std::endl
				<< "maxB " << maxB << std::endl;
				return;
				colA.onCollide(entity, other);
				colB.onCollided(entity, other);
			}
		}
	}
}