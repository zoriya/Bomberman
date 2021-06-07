//
// Created by Louis Auzuret on 06/03/21
//

#pragma once

#include "Component/Controllable/ControllableComponent.hpp"
#include "Models/Vector2.hpp"
#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Controllable entities in a menu.
	class MenuControllableSystem : public WAL::System<ControllableComponent>
	{
	private:
		//! @brief reference to wal
		WAL::Wal &wal;

		//! @brief index of the current button selected
		int _buttonIndex = 0;

		//! @brief move vector
		Vector2f move;

		//! @brief Select action
		bool select = false;

		//! @brief Cancel action
		bool cancel = false;

		//! @brief update button index
		//! @param length length of the button set
		void updateButtonIndex(int length);

		//! @brief time (in mili second) since last check
		std::chrono::milliseconds _now;
	public:
		//! @inherit
		void onSelfUpdate(void) override;

		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<ControllableComponent> &entities) override;

		//! @brief A default constructor
		MenuControllableSystem(WAL::Wal &wal);
		//! @brief A MenuControllable system is not copy constructable
		MenuControllableSystem(const MenuControllableSystem &) = delete;
		//! @brief A default destructor
		~MenuControllableSystem() override = default;
		//! @brief A MenuControllable system is assignable.
		MenuControllableSystem &operator=(const MenuControllableSystem &) = default;
	};
}
