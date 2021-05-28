//
// Created by Louis Auzuret on 5/20/21
//

#include "Component/Collision/CollisionComponent.hpp"
#include "System/Collision/CollisionSystem.hpp"
#include "Component/Drawable/Drawable3DComponent.hpp"
#include "BoundingBox.hpp"

namespace BBM
{
	CollisionSystem::CollisionSystem(WAL::Wal &wal)
	: WAL::System({}), _wal(wal)
	{

	}
	void CollisionSystem::onFixedUpdate(WAL::Entity &entity)
	{
		try {
			auto &collision = entity.getComponent<CollisionComponent>();
			auto &drawable = entity.getComponent<Drawable3DComponent>();
			for (auto &other : _wal.scene.getEntities()) {
				auto otherDrawable3D = other.getComponent<Drawable3DComponent>();

				if (RAY::BoundingBox::collision(*(drawable.member.get()),
											*(otherDrawable3D.member.get())))
					collision.onCollide(entity, other);		

			}
		} catch (std::exception &e) {
			return;
		}

	}
}