//
// Created by Zoe Roux on 5/17/21.
//

#include "Component/Position/PositionComponent.hpp"
#include "System/Movable/MovableSystem.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Wal.hpp"

namespace WAL
{
	const std::type_info &MovableSystem::getComponent() const
	{
		return typeid(MovableComponent);
	}

	void MovableSystem::onFixedUpdate(Entity &entity)
	{
		auto &movable = entity.getComponent<MovableComponent>();
		auto &position = entity.getComponent<PositionComponent>();

		position.position += movable._velocity * Wal::timestep.count();
		movable._velocity = movable._acceleration * Wal::timestep.count();
		movable._acceleration = Vector3f();
	}
}