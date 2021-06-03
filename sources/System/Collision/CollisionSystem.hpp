
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
	class CollisionSystem : public WAL::System<PositionComponent, CollisionComponent>
	{
	public:
		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		explicit CollisionSystem(WAL::Wal &wal);
		//! @brief A Collision system is copy constructable
		CollisionSystem(const CollisionSystem &) = default;
		//! @brief A default destructor
		~CollisionSystem() override = default;
		//! @brief A system is not assignable.
		CollisionSystem &operator=(const CollisionSystem &) = delete;

		//! @brief check AABB collision
		static bool collide(Vector3f minA, Vector3f maxA, Vector3f minB, Vector3f maxB);
	};
}