//
// Created by Tom Augier on 2021-06-09.
//

#include "GravitySystem.hpp"

namespace BBM
{
	GravitySystem::GravitySystem(WAL::Wal &wal)
		: System(wal)
	{}

	void GravitySystem::onFixedUpdate(WAL::ViewEntity<GravityComponent, MovableComponent, PositionComponent> &entity)
	{
		auto &movable = entity.get<MovableComponent>();
		auto &position = entity.get<PositionComponent>();

		if (position.getY() > 0)
			movable.addForce(Vector3f(0, -0.1, 0));
	}
}