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
	ControllableSystem::ControllableSystem()
		: WAL::System({
			typeid(ControllableComponent),
			typeid(MovableComponent)
		})
	{}

	void ControllableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &controllable = entity.getComponent<ControllableComponent>();
		auto &movable = entity.getComponent<MovableComponent>();

		movable.addForce(Vector3f(controllable.moveX, controllable.jump, controllable.moveZ));
	}
}