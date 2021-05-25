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
	class BombHolderComponent : public WAL::Component
	{

		private:
			//! @brief bomb count of an entity
			unsigned int _bombCount;
			//! @brief max bomb count of an entity
			unsigned int _maxBombCount;

		public:
			//! @brief add bomb to the entity
			void addBomb(unsigned int bombCount);
			
			//! @brief add bomb bax of the entity
			void addMaxBombCount(unsigned int maxBombCount);

			//! @brief reduce bomb max of the entity
			void removeMaxBombCount(unsigned int bombCount);
			
			//! @brief reduce bomb
			void removeBomb(unsigned int bombCount);

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;
			
			//! @brief A component can't be instantiated, it should be derived.
			explicit BombHolderComponent(WAL::Entity &entity);

			//! @brief Constructor
			BombHolderComponent(WAL::Entity &entity, unsigned int maxBombCount);

			//! @brief A component can't be instantiated, it should be derived.
			BombHolderComponent(const BombHolderComponent &) = default;

			//! @brief default destructor
			~BombHolderComponent() override = default;

			//! @brief A component can't be assigned
			BombHolderComponent &operator=(const BombHolderComponent &) = delete;
	};
}