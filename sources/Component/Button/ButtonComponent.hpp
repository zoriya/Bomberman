//
// Created by Louis Auzuret on 06/03/21
//

#pragma once

#include "Models/Callback.hpp"
#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include <optional>
#include "Wal.hpp"

namespace BBM
{
	enum ButtonComponentType { IDLE, CLICK, HOVER };

	template<enum ButtonComponentType T>
	class ButtonComponent: public WAL::Component
	{	
		public:
			//! @brief onEvent callback
			WAL::Callback<WAL::Entity &, WAL::Wal &> onEvent;

			//! @brief button which is at the top of this button
			WAL::Entity *_up;
			//! @brief button which is below of this button
			WAL::Entity *_down;
			//! @brief button which is on the right of this button
			WAL::Entity *_right;
			//! @brief button which is on the left of this button
			WAL::Entity *_left;
			
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
			ButtonComponent(WAL::Entity &entity, WAL::Callback<WAL::Entity &, WAL::Wal &> callback)
				:	WAL::Component(entity),
					onEvent(callback), _up(nullptr), _down(nullptr), _right(nullptr), _left(nullptr)
			{ }

			ButtonComponent &setButtonLinks(WAL::Entity *up = nullptr, WAL::Entity *down = nullptr,
							WAL::Entity *left = nullptr, WAL::Entity *right = nullptr)
			{
				this->_up = up;
				this->_down = down;
				this->_left = left;
				this->_right = right;
				return *this;
			}	

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
