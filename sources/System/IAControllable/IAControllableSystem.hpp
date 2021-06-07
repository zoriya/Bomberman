//
// Created by Louis Auzuret on 06/07/21
//

#pragma once

#include "System/System.hpp"

namespace BBM
{
	//! @brief A system to handle keyboard entities.
	class IAControllableSystem : public WAL::System<ControllableComponent, IAControllableComponent>
	{
	private:
		//! @brief extract a number from the lua stack
		float getReturnNumber(lua_State *state);
		//! @brief extract a bool from the lua stack
		bool getReturnBool(lua_State *state);
	public:
		//! @inherit
		void onFixedUpdate(WAL::ViewEntity<ControllableComponent, IAControllableComponent> &entity) override;

		//! @brief A default constructor
		IAControllableSystem(WAL::Wal &wal);
		//! @brief A keyboard system is copy constructable
		IAControllableSystem(const IAControllableSystem &) = default;
		//! @brief A default destructor
		~IAControllableSystem() override = default;
		//! @brief A keyboard system is assignable.
		IAControllableSystem &operator=(const IAControllableSystem &) = default;
	};
}
