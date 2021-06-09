//
// Created by Louis Auzuret on 06/07/21
//

#include "Map/MapInfo.hpp"
#include "Component/Controllable/ControllableComponent.hpp"
#include "Component/IAControllable/IAControllableComponent.hpp"
#include "System/IAControllable/IAControllableSystem.hpp"

namespace BBM
{
	IAControllableSystem::IAControllableSystem(WAL::Wal &wal)
	: System(wal)
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

	void IAControllableSystem::onFixedUpdate(WAL::ViewEntity<ControllableComponent, IAControllableComponent> &entity)
	{
		auto &ia = entity.get<IAControllableComponent>();
		auto &controllable = entity.get<ControllableComponent>();
		MapInfo info({1, 2, 3}, MapGenerator::NOTHING);

		luabridge::LuaRef updateFunc = luabridge::getGlobal(ia.state, "Update");
		if (!updateFunc.isFunction())
			return;	
		luabridge::LuaResult res = updateFunc(info);

		if (res.hasFailed() || res.size() != 4)
			return;
		controllable.bomb = res[3];
		controllable.jump = res[2];
		controllable.move.y = res[1];
		controllable.move.x = res[0];
	}
}