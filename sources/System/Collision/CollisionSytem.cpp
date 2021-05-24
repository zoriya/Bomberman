//
// Created by Louis Auzuret on 5/20/21
//

#include "lib/wal/sources/Component/Movable/MovableComponent.hpp"
#include "lib/wal/sources/Component/Position/PositionComponent.hpp"
#include "sources/Component/Collision/CollisionComponent.hpp"
#include "sources/System/Collision/CollisionSystem.hpp"

namespace BBM
{
	const std::type_info &CollisionSystem::getComponent() const
	{
		return typeid(CollisionComponent);
	}

	void CollisionSystem::onFixedUpdate(WAL::Entity &entity)
	{
		try {
			auto &movable = entity.getComponent<WAL::MovableComponent>();
			auto &position = entity.getComponent<WAL::PositionComponent>();
			auto &collision = entity.getComponent<CollisionComponent>();
			WAL::Vector3f minA(position.getX(), position.getY(), position.getZ());
			WAL::Vector3f maxA(	minA.x + collision.getBoundX(),
								minA.y + collision.getBoundY(),
								minA.z + collision.getBoundZ());
		} catch (std::exception &e) {
			return;
		}
		/*auto sceneEntities = sceneManager.getCurrentScene().getEntities();
		for (auto sceneEntity : sceneEntities) {
			try {
				auto &otherPosition = sceneEntity.getComponent<WAL::PositionComponent>();
				auto &otherCollision = sceneEntity.getComponent<CollisionComponent>();
				WAL::Vector3f minB(	otherPosition.getX(),
									otherPosition.getY(),
									otherPosition.getZ());
				WAL::Vector3f maxB(	minB.x + otherCollision.getBoundX(),
									minB.y + otherCollision.getBoundY(),
									minB.z + otherCollision.getBoundZ());
				if 	(minA.x <= maxB.x && maxA.x >= minB.x) &&
        			(minA.y <= maxB.y && maxA.y >= minB.y) &&
        			(minA.z <= maxB.z && maxA.z >= minB.z)
					movable.setForce(0);
			} catch (std::exception &e) {
				continue;
			}
		}*/
	}
}