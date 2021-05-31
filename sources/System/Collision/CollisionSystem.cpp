//
// Created by Louis Auzuret on 5/20/21
//

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
		try {
			auto &posA = entity.getComponent<PositionComponent>();
			auto &col = entity.getComponent<CollisionComponent>();
			Vector3f minA = {	std::min(posA.getX(), posA.getX() + col.getBoundX()),
								std::min(posA.getY(), posA.getY() + col.getBoundY()),
								std::min(posA.getZ(), posA.getZ() + col.getBoundZ())};	
			Vector3f maxA = {	std::max(posA.getX(), posA.getX() + col.getBoundX()),
								std::max(posA.getY(), posA.getY() + col.getBoundY()),
								std::max(posA.getZ(), posA.getZ() + col.getBoundZ())};
			for (auto &other : _wal.scene->getEntities()) {
				auto &colB = entity.getComponent<CollisionComponent>();
				auto &posB = other.getComponent<PositionComponent>();
				Vector3f minB = {	std::min(posB.getX(), posB.getX() + colB.getBoundX()),
									std::min(posB.getY(), posB.getY() + colB.getBoundY()),
									std::min(posB.getZ(), posB.getZ() + colB.getBoundZ())};	
				Vector3f maxB = {	std::max(posB.getX(), posB.getX() + colB.getBoundX()),
									std::max(posB.getY(), posB.getY() + colB.getBoundY()),
									std::max(posB.getZ(), posB.getZ() + colB.getBoundZ())};
				if ((minA.x <= maxB.x && maxA.x >= minB.x) &&
        			(minA.y <= maxB.y && maxA.y >= minB.y) &&
         			(minA.z <= maxB.z && maxA.z >= minB.z))
					col.onCollide(entity, other);
			}
		} catch (std::exception &e) {
			return;
		}
	}
}