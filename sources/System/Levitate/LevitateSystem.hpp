//
// Created by hbenjamin on 07/06/2021.
//

#pragma once

#include "Component/Levitate/LevitateComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Wal.hpp"
#include "System/System.hpp"

namespace BBM {
	class LevitateSystem : public WAL::System
	{
	private:
	public:
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		LevitateSystem();
		//! @brief A Levitate system is copy constructable
		LevitateSystem(const LevitateSystem &) = default;
		//! @brief A default destructor
		~LevitateSystem() override = default;
		//! @brief A Levitate system is assignable.
		LevitateSystem &operator=(const LevitateSystem &) = default;
	};
}