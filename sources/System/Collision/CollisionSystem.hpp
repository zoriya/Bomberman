
//
// Created by Louis Auzuret on 5/20/21
//

#pragma once

#include <algorithm>
#include "Wal.hpp"
#include "System/System.hpp"

namespace BBM
{
    //! @brief A system to handle collisions.
    class CollisionSystem : public WAL::System
    {
	private:
		WAL::Wal &_wal;
    public:
        //! @inherit
        void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		CollisionSystem(WAL::Wal &wal);
		//! @brief A movable system is copy constructable
		CollisionSystem(const CollisionSystem &) = default;
		//! @brief A default destructor
		~CollisionSystem() override = default;
		//! @brief A movable system is assignable.
		CollisionSystem &operator=(const CollisionSystem &) = default;
    };
}