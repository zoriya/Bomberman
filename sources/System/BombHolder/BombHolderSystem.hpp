//
// Created by Zoe Roux on 5/31/21.
//

#pragma once

#include <System/System.hpp>
#include <Wal.hpp>
#include "Models/Vector3.hpp"

namespace BBM
{
	//! @brief The system that allow one to place bombs.
	class BombHolderSystem : public WAL::System
	{
	private:
		//! @brief A reference to the engine to spawn new entities.
		WAL::Wal &_wal;
		//! @brief Spawn a bomb at the specified position.
		void _spawnBomb(Vector3f position);

		//! @brief The method triggered when the bomb explode.
		static void _bombExplosion(WAL::Entity &bomb, WAL::Wal &);
	public:
		//! @brief The explosion time of new bombs.
		static std::chrono::nanoseconds explosionTimer;
		//! @brief The radius of the explosion.
		static float explosionRadius;

		//! @inherit
		void onUpdate(WAL::Entity &entity, std::chrono::nanoseconds dtime) override;

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
