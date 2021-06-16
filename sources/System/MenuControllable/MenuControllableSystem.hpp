//
// Created by Louis Auzuret on 06/03/21
//

#pragma once

#include "Component/Controllable/ControllableComponent.hpp"
#include "Models/Vector2.hpp"
#include "System/System.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Renderer/Drawable2DComponent.hpp"
#include "Component/Button/ButtonComponent.hpp"

namespace BBM
{
	//! @brief A system to handle Controllable entities in a menu.
	class MenuControllableSystem : public WAL::System<>
	{
	private:
		//! @brief index of the current button selected
		WAL::Entity *_currentButton;

		//! @brief update current button reference
		//! @param selected lets know if te new selected button is 'pressed'
		void _updateCurrentButton(bool selected, Vector2f move);

		//! @return true if mouse on entity
		bool _mouseOnButton(WAL::ViewEntity<OnClickComponent, OnHoverComponent, OnIdleComponent, PositionComponent, Drawable2DComponent> &entity) const;
	public:
		//! @brief time (in millisecond) since last check
		std::chrono::time_point<std::chrono::steady_clock> now;
		//! @inherit
		void onSelfUpdate() override;

		//! @brief A default constructor
		explicit MenuControllableSystem(WAL::Wal &wal);
		//! @brief A MenuControllable system is not copy constructable
		MenuControllableSystem(const MenuControllableSystem &) = delete;
		//! @brief A default destructor
		~MenuControllableSystem() override = default;
		//! @brief A MenuControllable system is not assignable.
		MenuControllableSystem &operator=(const MenuControllableSystem &) = delete;
	};
}
