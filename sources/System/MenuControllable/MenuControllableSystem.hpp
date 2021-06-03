//
// Created by Louis Auzuret on 06/03/21
//

#pragma once

#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle Controllable entities in a menu.
	class MenuControllableSystem : public WAL::System
	{
	private:
		unsigned _buttonIndex = 0;
	public:

		//! @inherit
		void onFixedUpdate(WAL::Entity &entity) override;

		//! @brief A default constructor
		MenuControllableSystem();
		//! @brief A MenuControllable system is not copy constructable
		MenuControllableSystem(const MenuControllableSystem &) = delete;
		//! @brief A default destructor
		~MenuControllableSystem() override = default;
		//! @brief A MenuControllable system is assignable.
		MenuControllableSystem &operator=(const MenuControllableSystem &) = default;
	};
}
