//
// Created by Zoe Roux on 5/24/21.
//

#pragma once

#include <System/System.hpp>
#include "Component/Position/PositionComponent.hpp"

namespace BBM
{
	//! @brief The system handling GridCenteredComponent
	class GridCenteredSystem : public WAL::System<GridCenteredComponent, MovableComponent, PositionComponent>
	{
	public:
		void onFixedUpdate(WAL::ViewEntity<GridCenteredComponent, MovableComponent, PositionComponent> &entity) override;

		//! @brief A default constructor
		explicit GridCenteredSystem(WAL::Wal &wal);
		//! @brief A GridCenteredSystem is copyable.
		GridCenteredSystem(const GridCenteredSystem &) = default;
		//! @brief A default destructor
		~GridCenteredSystem() override = default;
		//! @brief A system is not assignable
		GridCenteredSystem &operator=(const GridCenteredSystem &) = delete;
	};
}
