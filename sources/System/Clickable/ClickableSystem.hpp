//
// Created by Louis Auzuret.
//

#pragma once

#include "wal/sources/System/System.hpp"

namespace BBM
{
	//! @brief A system to handle movable entities. This system update velocity based on accelerations and positions based on velocity.
	class ClickableSystem : public WAL::System
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		ClickableSystem(void);
		//! @brief A clickable system is copy constructable
		ClickableSystem(const ClickableSystem &) = default;
		//! @brief A default destructor
		~ClickableSystem() override = default;
		//! @brief A clickable system is assignable.
		ClickableSystem &operator=(const ClickableSystem &) = default;
	};
} //namespace BBM
