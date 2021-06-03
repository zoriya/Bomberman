//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "Component/Movable/MovableComponent.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Controllable entities.
	class ControllableSystem : public WAL::System<ControllableComponent, MovableComponent>
	{
	public:
		//! @brief The speed applied to every controllable entities.
		static constexpr const float speed = .25f;

		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		explicit ControllableSystem(WAL::Wal &wal);
		//! @brief A Controllable system is copy constructable
		ControllableSystem(const ControllableSystem &) = default;
		//! @brief A default destructor
		~ControllableSystem() override = default;
		//! @brief A system is not assignable.
		ControllableSystem &operator=(const ControllableSystem &) = delete;
	};
}
