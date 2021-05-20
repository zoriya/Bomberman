//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#pragma once

#include <string>
#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"
#include "lib/wal/sources/Models/Vector3.hpp"

class BombComponent : public WAL::Component
{

	public:
		//! @brief Enum of bomb type
		enum BombType {
			CLASSIC,
			REMOTE,
			STICKY,
			DANGEROUS,
			THROWABLE
		};
		//! @brief Constructor
		BombComponent(WAL::Entity &entity, BombType bombType, unsigned int ownerUid);
		~BombComponent() override = default;
		//! @brief A bomb component is copyable
		BombComponent(const BombComponent &) = default;
		//! @brief A bomb component is assignable
		BombComponent &operator=(const BombComponent &) = delete;

		//! @brief Get the remaining time of the bomb
		unsigned getCountdown() const;
		//! @brief Get the explosion dist of the bomb
		unsigned getExplosionDist() const;
		//! @brief Get the explosion height of the bomb
		unsigned getExplosionHeight() const;
		//! @brief Get the damage of the bomb
		unsigned getExplosionDamage() const;
		//! @brief Get the owner uid
		unsigned getOwnerUid() const;
		//! @brief Is able to break wall
		bool isBreakingWall() const;
		//! @brief Is able to pass through wall
		bool isGhosting() const;

		//! @brief Set the remaining time of the bomb
		void setCountdown(unsigned countdown);
		//! @brief Set the explosion dist of the bomb
		void setExplosionDist(unsigned explosionDist);
		//! @bries Set the explosion height of the bomb
		void setExplosionHeight(unsigned explosionHeight);
		//! @brief Set the damage of the bomb
		void setExplosionDamage(unsigned explosionDamage);
		//! @brief Set the owner uid
		void setOwnerUid(unsigned isOwnerUid);
		//! @brief Set ability to break wall
		void setBreakingWall(bool isBreakingWall);
		//! @brief set ability to pass through wall
		void setGhosting(bool isGhosting);

	private:
        //! @brief Direction enum
		enum Direction {
			UP,
			RIGHT,
			DOWN,
			LEFT,
			VERTICAL, // UP + DOWN
			HORIZONTAL, // RIGHT + LEFT
			CLASSIC, // UP + LEFT + RIGHT + DOWN
			ALL, // SQUARE AROUND
		};

		//! @brief Pass through walls
		bool _isGhosting;
        //! @brief Is bomb breaking wall
		bool _isBreakingWall;
        //! @brief Explosion range of the bomb
		unsigned _explosionDist;
		//! @brief Explosion height
		unsigned _explosionHeight;
        //! @brief The time remaining before the explosion
		unsigned _countdown;
        //! @brief The damage of the bomb (on player)
		unsigned _explosionDamage;
        //! @brief The owner uid of the bomb
		unsigned _ownerUid;
		//! @brief bombType
		BombComponent::BombType _bombType;

	protected:
};