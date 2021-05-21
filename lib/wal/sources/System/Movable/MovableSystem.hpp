
//
// Created by Zoe Roux on 5/17/21.
//

#pragma once

#include "System/System.hpp"

namespace WAL
{
	//! @brief A system to handle movable entities. This system update velocity based on accelerations and positions based on velocity.
	class MovableSystem : public System
	{
	public:
		//! @inherit
		void onFixedUpdate(Entity &entity) override;

		//! @brief A default constructor
		MovableSystem();
		//! @brief A movable system is copy constructable
		MovableSystem(const MovableSystem &) = default;
		//! @brief A default destructor
		~MovableSystem() override = default;
		//! @brief A movable system is assignable.
		MovableSystem &operator=(const MovableSystem &) = default;
	};
}
