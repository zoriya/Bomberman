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

	float IAControllableSystem::getReturnNumber(lua_State *state)
	{
		float res = 0;

		if (lua_isnil(state, -1))
			return res;
		if (!lua_isnumber(state, -1))
			return res;
		res = lua_tonumber(state, -1);
		lua_pop(state, 1);

		return res;
	}

	bool IAControllableSystem::getReturnBool(lua_State *state)
	{
		bool res = false;

		if (lua_isnil(state, -1))
			return res;
		if (!lua_isboolean(state, -1))
			return res;
		res = lua_toboolean(state, -1);
		lua_pop(state, 1);
		return res;
	}

	void IAControllableSystem::onFixedUpdate(WAL::Entity &entity)
	{
		auto &ia = entity.getComponent<IAControllableComponent>();
		auto &controllable = entity.getComponent<ControllableComponent>();

		lua_getglobal(ia.state, "Update");
		//push parameters
		int nbParams = 0;
		int nbReturn = 4;
		lua_pcall(ia.state, nbParams, nbReturn, 0);
		controllable.bomb = getReturnBool(ia.state);
		controllable.jump = getReturnBool(ia.state);
		controllable.move.y = getReturnNumber(ia.state);
		controllable.move.x = getReturnNumber(ia.state);
	}
}