//
// Created by Tom Augier on 2021-06-09.
//

#pragma once

#include "Component/Movable/MovableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Gravity/GravityComponent.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Gravity entities.
	class GravitySystem : public WAL::System<GravityComponent, MovableComponent, PositionComponent>
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<GravityComponent, MovableComponent, PositionComponent> &entity) override;

		//! @brief A default constructor
		explicit GravitySystem(WAL::Wal &wal);
		//! @brief A Gravity system is copy constructable
		GravitySystem(const GravitySystem &) = default;
		//! @brief A default destructor
		~GravitySystem() override = default;
		//! @brief A system is not assignable.
		GravitySystem &operator=(const GravitySystem &) = delete;
	};
}