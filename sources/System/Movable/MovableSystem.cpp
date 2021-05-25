//
// Created by Zoe Roux on 5/17/21.
//

#include "Component/Position/PositionComponent.hpp"
#include "MovableSystem.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "Wal.hpp"

namespace BBM
{
	MovableSystem::MovableSystem()
		: WAL::System({
			typeid(MovableComponent),
			typeid(PositionComponent)
		})
	{}

	void MovableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &movable = entity.getComponent<MovableComponent>();
		auto &position = entity.getComponent<PositionComponent>();

		position.position += movable._velocity * WAL::Wal::timestep.count();
		movable._velocity = movable._acceleration * WAL::Wal::timestep.count();
		movable._acceleration = WAL::Vector3f();
	}
} // namespace WAL