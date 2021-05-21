//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

namespace BBM 
{
	class ControllableComponent : public WAL::Component
	{
	private:
		float _moveX = 0;
		float _moveZ = 0;
		bool _jump = false;
		bool _bomb = false;
		bool _pause = false;
	public:

		//! @inherit
		WAL::Component *clone(WAL::Entity &entity) const override;

		//! @brief A component can't be instantiated, it should be derived.
		explicit ControllableComponent(WAL::Entity &entity);

		//! @brief Constructor
		ControllableComponent(WAL::Entity &entity, unsigned int maxBombCount);

		//! @brief A component can't be instantiated, it should be derived.
		ControllableComponent(const ControllableComponent &) = default;

		//! @brief default destructor
		~ControllableComponent() override = default;

		//! @brief A component can't be assigned
		ControllableComponent &operator=(const ControllableComponent &) = delete;

		friend class KeyboardSystem;
		friend class ControllableSystem;
	};
}