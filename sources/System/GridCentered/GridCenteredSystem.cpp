//
// Created by Zoe Roux on 5/24/21.
//

#include "Component/Movable/MovableComponent.hpp"
#include "Component/GridCentered/GridCenteredComponent.hpp"
#include "GridCenteredSystem.hpp"

namespace BBM
{
	GridCenteredSystem::GridCenteredSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void GridCenteredSystem::onFixedUpdate(WAL::ViewEntity<GridCenteredComponent, MovableComponent, PositionComponent> &entity)
	{
		auto &grid = entity.get<GridCenteredComponent>();
		auto &movement = entity.get<MovableComponent>();
//		movement.addForce(grid.force * )
	}
}