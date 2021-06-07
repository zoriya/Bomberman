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

	bool CollisionSystem::boxesCollide(Vector3f minA, Vector3f maxA, Vector3f minB, Vector3f maxB)
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
		Vector3f pointAx;
		Vector3f pointAy;
		Vector3f pointAz;

		if (auto *movable = entity->tryGetComponent<MovableComponent>()) {
			auto vel = movable->getVelocity();
			pointAx.x += vel.x;
			pointAy.y += vel.y;
			pointAz.z += vel.z;
		}

		Vector3f minAx = Vector3f::min(pointAx, pointAx + colA.bound);
		Vector3f maxAx = Vector3f::max(pointAx, pointAx + colA.bound);

		Vector3f minAy = Vector3f::min(pointAy, pointAy + colA.bound);
		Vector3f maxAy = Vector3f::max(pointAy, pointAy + colA.bound);

		Vector3f minAz = Vector3f::min(pointAz, pointAz + colA.bound);
		Vector3f maxAz = Vector3f::max(pointAz, pointAz + colA.bound);

		for (auto &[other, posB, colB] : this->getView()) {
			if (other.getUid() == entity->getUid())
				continue;

			auto pointB = posB.position + colB.positionOffset;
			int collidedAxis = 0;

			// TODO if B is also a movable we don't check with it's changing position
			Vector3f minB = Vector3f::min(pointB, pointB + colB.bound);
			Vector3f maxB = Vector3f::max(pointB, pointB + colB.bound);

			if (boxesCollide(minAx, maxAx, minB, maxB)) {
			/*	std::cout << "collided" << std::endl
				<< "minA " << minA << std::endl
				<< "maxA " << maxA << std::endl
				<< "minB " << minB << std::endl
				<< "maxB " << maxB << std::endl;*/
				//return;
				collidedAxis += CollisionComponent::CollidedAxis::X;
			}
			if (boxesCollide(minAy, maxAy, minB, maxB)) {
				collidedAxis += CollisionComponent::CollidedAxis::Y;
			}
			if (boxesCollide(minAz, maxAz, minB, maxB)) {
				collidedAxis += CollisionComponent::CollidedAxis::Z;
			}
			if (collidedAxis) {
				colA.onCollide(entity, other, collidedAxis);
				colB.onCollided(entity, other, collidedAxis);
			}
		}
	}
}