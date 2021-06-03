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

	void MovableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &movable = entity.getComponent<MovableComponent>();
		auto &position = entity.getComponent<PositionComponent>();

		position.position += movable._velocity;
		movable._velocity = movable._acceleration;
		movable._acceleration = Vector3f();
	}
} // namespace WAL