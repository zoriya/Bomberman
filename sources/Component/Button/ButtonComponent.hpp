//
// Created by Louis Auzuret on 06/03/21
//

#pragma once

#include "Models/Callback.hpp"
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"

namespace BBM
{
	enum ButtonComponentType { IDLE, CLICK, HOVER };

	template<enum ButtonComponentType T>
	class ButtonComponent: public WAL::Component
	{	
		public:
			//! @brief onEvent callback
			WAL::Callback<WAL::Entity &> onEvent;
			
			//! @inherit
			WAL::Component *clone(WAL::Entity &entity) const override
			{
				return new ButtonComponent(entity, onEvent);
			}

			//! @brief Initialize a new Button component.
			explicit ButtonComponent(WAL::Entity &entity)
				: WAL::Component(entity), onEvent()
			{ }

			//! @brief Constructor with the 3 callback
			ButtonComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &> callback)
				:	WAL::Component(entity),
					onEvent(callback)
			{ }

			//! @brief A Controllable component is copy constructable.
			ButtonComponent(const ButtonComponent<T> &) = default;
			//! @brief default destructor
			~ButtonComponent() override = default;
			//! @brief A Button component default assign operator
			ButtonComponent<T> &operator=(const ButtonComponent<T> &) = default;

			//! @brief Empty button callback
			static void emptyButtonCallback(WAL::Entity &)
			{ }
	};
	typedef ButtonComponent<IDLE> OnIdleComponent;
	typedef ButtonComponent<CLICK> OnClickComponent;
	typedef ButtonComponent<HOVER> OnHoverComponent;
}
