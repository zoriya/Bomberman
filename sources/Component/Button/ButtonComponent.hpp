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
			WAL::Callback<> onIdle;

			//! @brief onHover callback
			WAL::Callback<> onHover;

			//! @brief onClick callback
			WAL::Callback<> onClick;
			

			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override;

			//! @brief Initialize a new Button component.
			explicit ButtonComponent(WAL::Entity &entity);

			//! @brief Constructor with the 3 callback
			ButtonComponent(WAL::Entity &entity, WAL::Callback<> idleCallback, WAL::Callback<> hoverCallback, WAL::Callback<> clickCallback);
			//! @brief A Controllable component is copy constructable.
			ButtonComponent(const ButtonComponent &) = default;
			//! @brief default destructor
			~ButtonComponent() override = default;
			//! @brief A Button component default assign operator
			ButtonComponent &operator=(const ButtonComponent &) = default;
	};
}