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
		auto &controllable = entity.getComponent<ControllableComponent>();
		auto &movable = entity.getComponent<WAL::MovableComponent>();

		movable.addForce(WAL::Vector3f(controllable._moveX, 0, controllable._moveZ));
	}
}