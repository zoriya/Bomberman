//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace Bomberman
{
	class ControllableComponent : public WAL::Component
	{	
		public:
			//! @brief input value for X axe
			float moveX = 0;
			//! @brief input value for Z axe
			float moveZ = 0;
			//! @brief input value for jump
			bool jump = false;
			//! @brief input value for bomb
			bool bomb = false;
			//! @brief input value for pause
			bool pause = false;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief A Controllable component can't be instantiated, it should be derived.
			explicit ControllableComponent(WAL::Entity &entity);

			//! @brief Constructor
			ControllableComponent(WAL::Entity &entity, unsigned int maxBombCount);

			//! @brief A Controllable component can't be instantiated, it should be derived.
			ControllableComponent(const ControllableComponent &) = default;

			//! @brief default destructor
			~ControllableComponent() override = default;

			//! @brief A Controllable omponent can't be assigned
			ControllableComponent &operator=(const ControllableComponent &) = delete;
	};
}