//
// Created by Zoe Roux on 6/9/21.
//

#pragma once

#include <System/System.hpp>
#include "Component/Position/PositionComponent.hpp"
#include "Component/Bomb/BasicBombComponent.hpp"

namespace BBM
{
	class BombSystem : public WAL::System<BasicBombComponent, PositionComponent>
	{
	public:
		//! @inherit
		void onUpdate(WAL::ViewEntity<BasicBombComponent, PositionComponent> &entity, std::chrono::nanoseconds dtime) override;

		//! @brief Construct a new bomb system.
		explicit BombSystem(WAL::Wal &wal);
		//! @brief A bomb system is copy constructable
		BombSystem(const BombSystem &) = default;
		//! @brief A default destructor
		~BombSystem() override = default;
		//! @brief A bomb system can't be assigned.
		BombSystem operator=(const BombSystem &) = delete;
	};
}
