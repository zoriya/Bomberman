//
// Created by Louis Auzuret on 06/07/21
//

#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/IAControllable/IAControllableComponent.hpp"
#include "System/IAControllable/IAControllableSystem.hpp"

namespace BBM
{
	IAControllableSystem::IAControllableSystem()
	: WAL::System({	typeid(IAControllableComponent),
					typeid(ControllableComponent)})
	{ }

	void IAControllableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &ia = entity.getComponent<IAControllableComponent>();
		auto &controllable = entity.getComponent<ControllableComponent>();

		lua_getglobal(ia.state, "update");
		//push parameters
		int nbParams = 0;
		int nbReturn = 1;
		lua_pcall(ia.state, nbParams, nbReturn, 0);
		if (lua_isnil(ia.state, -1))
			return;
		if (!lua_isnumber(ia.state, -1))
			return;
		controllable.move.y = lua_tonumber(ia.state, -1);
		lua_pop(ia.state, 1);
	}
}