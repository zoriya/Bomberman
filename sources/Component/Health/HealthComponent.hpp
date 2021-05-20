//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace BBM 
{
	class HealthComponent : public WAL::Component
	{

		private:
			//! @brief life of an entity
			unsigned int _healthPoint;

		public:
			//! @brief add health to the entity
			void addHealthPoint(unsigned int healthPoint);
			
			//! @brief reduce health
			void takeDmg(unsigned int damage);

			//! @brief health to 0
			void die(void);

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A component can't be instantiated, it should be derived.
			explicit HealthComponent(WAL::Entity &entity);

			//! @brief Constructor
			HealthComponent(WAL::Entity &entity, unsigned int healthPoint);

			//! @brief A component can't be instantiated, it should be derived.
			HealthComponent(const HealthComponent &) = default;

			//! @brief default destructor
			~HealthComponent() override = default;

			//! @brief A component can't be assigned
			HealthComponent &operator=(const HealthComponent &) = delete;

			friend class HealthSystem;
	};
}