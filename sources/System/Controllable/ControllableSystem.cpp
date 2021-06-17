//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "ControllableSystem.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	ControllableSystem::ControllableSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void ControllableSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent, MovableComponent> &entity)
	{
		auto &controllable = entity.get<ControllableComponent>();
		auto &movable = entity.get<MovableComponent>();
		auto health = entity->tryGetComponent<HealthComponent>();
		Vector2f move = controllable.move.normalized() * controllable.speed;

		if (health && health->getHealthPoint() <= 0)
			return;
		movable.addForce(Vector3f(move.x, 0, move.y));
	}
}