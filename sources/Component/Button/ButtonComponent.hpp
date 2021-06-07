//
// Created by Louis Auzuret on 06/03/21
//

#pragma once

#include "Models/Callback.hpp"
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	class ButtonComponent : public WAL::Component
	{	
		public:
			//! @brief onIdle callback
			WAL::Callback<WAL::Entity &> onIdle;

			//! @brief onHover callback
			WAL::Callback<WAL::Entity &> onHover;

			//! @brief onClick callback, when the mouse button is released
			WAL::Callback<WAL::Entity &> onClick;

			//! @brief onHold callback, when the mouse button is pressed
			WAL::Callback<WAL::Entity &> onHold;
			

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Initialize a new Button component.
			explicit ButtonComponent(WAL::Entity &entity);

			//! @brief Constructor with the 3 callback
			ButtonComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &> idleCallback, WAL::Callback<WAL::Entity &> hoverCallback,
			WAL::Callback<WAL::Entity &> clickCallback, WAL::Callback<WAL::Entity &> holdCallback);

			//! @brief A Controllable component is copy constructable.
			ButtonComponent(const ButtonComponent &) = default;
			//! @brief default destructor
			~ButtonComponent() override = default;
			//! @brief A Button component default assign operator
			ButtonComponent &operator=(const ButtonComponent &) = default;

			//! @brief Empty button callback
			static void emptyButtonCallback(WAL::Entity &);
	};
}