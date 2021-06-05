//
// Created by Zoe Roux on 5/17/21.
//

#include "Component/Position/PositionComponent.hpp"
#include "MovableSystem.hpp"
#include "Component/Movable/MovableComponent.hpp"

namespace BBM
{
	MovableSystem::MovableSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void MovableSystem::onFixedUpdate(WAL::ViewEntity<MovableComponent, PositionComponent> &entity)
	{
		auto &movable = entity.get<MovableComponent>();
		auto &position = entity.get<PositionComponent>();

		position.position += movable._velocity;
		movable._velocity = movable._acceleration;
		movable._acceleration = Vector3f();
	}
} // namespace WAL