//
// Created by Zoe Roux on 5/31/21.
//

#pragma once

#include <System/System.hpp>
#include <Wal.hpp>
#include <Component/Collision/CollisionComponent.hpp>
#include "Models/Vector3.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/BombHolder/BombHolderComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"

namespace BBM
{
	enum ExpansionDirection
	{
		UP = 1,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8,
		FRONT = 16,
		BACK = 32
	};

	//! @brief The system that allow one to place bombs.
	class BombHolderSystem : public WAL::System<PositionComponent, BombHolderComponent, ControllableComponent>
	{
	private:
		//! @brief Spawn a bomb at the specified position.
		void _spawnBomb(Vector3f position, BombHolderComponent &holder, unsigned id);

		//! @brief Spawn a bomb at the specified position.
		static void _dispatchExplosion(const Vector3f &position, WAL::Wal &wal, int radiusToDo,
		                               ExpansionDirection expansionDirections);

		//! @brief Wrapped call to specify default arg value
		inline static void _dispatchExplosion(const Vector3f &position, WAL::Wal &wal, int radiusToDo)
		{
			return _dispatchExplosion(position,
			                          wal,
			                          radiusToDo,
			                          static_cast<ExpansionDirection>(
				                          ExpansionDirection::DOWN
				                          | ExpansionDirection::UP
				                          | ExpansionDirection::FRONT
				                          | ExpansionDirection::BACK
				                          | ExpansionDirection::LEFT
				                          | ExpansionDirection::RIGHT
			                          )
			);
		};

		//! @brief The method triggered when the bomb explode.
		static void _bombExplosion(WAL::Entity &bomb, WAL::Wal &);

		//! @brief The method called when a player collide with a bomb.
		static void
		_bombCollide(WAL::Entity &entity, const WAL::Entity &wall, BBM::CollisionComponent::CollidedAxis collidedAxis);

	public:
		//! @brief The explosion time of new bombs.
		static std::chrono::nanoseconds explosionTimer;

		//! @inherit
		void onUpdate(WAL::ViewEntity<PositionComponent, BombHolderComponent, ControllableComponent> &entity,
		              std::chrono::nanoseconds dtime) override;

		//! @brief A default constructor
		explicit BombHolderSystem(WAL::Wal &wal);

		//! @brief A bomb holder system is copy constructable
		BombHolderSystem(const BombHolderSystem &) = default;

		//! @brief A default destructor
		~BombHolderSystem() override = default;

		//! @brief A bomb holder system is not assignable.
		BombHolderSystem &operator=(const BombHolderSystem &) = delete;
	};
}
