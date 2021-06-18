//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "ControllableSystem.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Speed/SpeedComponent.hpp"
#include "Component/Health/HealthComponent.hpp"

namespace BBM
{
	ControllableSystem::ControllableSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void ControllableSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent, MovableComponent> &entity)
	{
		auto &controllable = entity.get<ControllableComponent>();
		// todo check why the .get doesn't work
		auto &speed = entity->getComponent<SpeedComponent>();
		auto &movable = entity.get<MovableComponent>();
		auto health = entity->tryGetComponent<HealthComponent>();
		Vector2f move = controllable.move.normalized() * speed.speed;

		movable.addForce(Vector3f(move.x, 0, move.y));
	}
}