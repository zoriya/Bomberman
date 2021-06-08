//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "ControllableSystem.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	ControllableSystem::ControllableSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void ControllableSystem::onUpdate(WAL::ViewEntity<ControllableComponent, MovableComponent> &entity, std::chrono::nanoseconds dtime)
	{
		auto &controllable = entity.get<ControllableComponent>();
		auto &movable = entity.get<MovableComponent>();
		Vector2f move = controllable.move.normalized() * controllable.speed;

		movable.addForce(Vector3f(move.x, controllable.jump, move.y));
		if (controllable.speed == 0.25f)
			return;
		controllable.nextSpeedBonusRate -= dtime;
		if (controllable.nextSpeedBonusRate <= 0ns) {
			controllable.nextSpeedBonusRate = controllable.speedBonusRate;
			controllable.speed = 0.25f;
		}
	}
}