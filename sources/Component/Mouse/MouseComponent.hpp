//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"
#include "Controllers/Mouse.hpp"

using Button RAY::Controller::Mouse::Button;

namespace BBM 
{
	class MouseComponent : public WAL::Component
	{
		public:

			//! @brief jump key
			int leftClick = MOUSE_BUTTON_LEFT;
			//! @brief bomb key
			int rightClick = MOUSE_BUTTON_RIGHT;
			//! @brief pause key
			int middleClick = MOUSE_BUTTON_MIDDLE;

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief A Mouse component can't be instantiated, it should be derived.
			explicit MouseComponent(WAL::Entity &entity);

			//! @brief A Mouse component can't be instantiated, it should be derived.
			MouseComponent(const MouseComponent &) = default;

			//! @brief default destructor
			~MouseComponent() override = default;

			//! @brief A Mouse component can't be assigned
			MouseComponent &operator=(const MouseComponent &) = delete;
	};
}