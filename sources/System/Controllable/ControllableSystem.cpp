//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#include "ControllableSystem.hpp"
#include "lib/wal/sources/Component/Movable/MovableComponent.hpp"
#include "sources/Component/Controllable/ControllableComponent.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace BBM
{
	const std::type_info &ControllableSystem::getComponent() const
	{
		return typeid(ControllableComponent);
	}

	void ControllableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &controllable= entity.getComponent<ControllableComponent>();
		auto &movable= entity.getComponent<WAL::MovableComponent>();

		if (controllable._left)
			movable.addForce(WAL::Vector3f(-1, 0, 0));
		if (controllable._right)
			movable.addForce(WAL::Vector3f(1, 0, 0));
		if (controllable._down)
			movable.addForce(WAL::Vector3f(0, 0, -1));
		if (controllable._up)
			movable.addForce(WAL::Vector3f(0, 0, 1));
		if (controllable._jump)
			movable.addForce(WAL::Vector3f(0, 1, 0));
	}
}