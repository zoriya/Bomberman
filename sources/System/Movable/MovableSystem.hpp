
//
// Created by Zoe Roux on 5/17/21.
//

#pragma once

#include "Component/Movable/MovableComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "System/System.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	//! @brief A system to handle movable entities. This system update velocity based on accelerations and positions based on velocity.
	class MovableSystem : public WAL::System<MovableComponent, PositionComponent>
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		explicit MovableSystem(WAL::Wal &wal);
		//! @brief A movable system is copy constructable
		MovableSystem(const MovableSystem &) = default;
		//! @brief A default destructor
		~MovableSystem() override = default;
		//! @brief A system is not assignable.
		MovableSystem &operator=(const MovableSystem &) = delete;
	};
} // namespace WAL
