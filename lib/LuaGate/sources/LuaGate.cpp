//
// Created by Louis Auzuret on 10/06/21
//

#include "LuaGate.hpp"

namespace LuaG
{
	State::State()
	: _state(luaL_newstate()), _shouldClose(true)
	{
		luaL_openlibs(_state);
	}

	State::State(lua_State *L, bool shouldClose)
	: _state(L), _shouldClose(shouldClose)
	{
	}

	State::~State()
	{
		if (_shouldClose)
			lua_close(_state);
	}

	lua_State *State::getState(void)
	{
		return _state;
	}

	void State::getGlobal(std::string str)
	{
		lua_getglobal(_state, str.c_str());
	}

	void State::dofile(std::string filepath)
	{
        luaL_dofile(_state, filepath.c_str());
	}

	void State::dostring(std::string str)
	{
        luaL_dostring(_state, str.c_str());
	}

	float State::getReturnNumber(void)
	{
		float res = 0;

		if (lua_isnil(_state, -1))
			return res;
		if (!lua_isnumber(_state, -1))
			return res;
		res = lua_tonumber(_state, -1);
		lua_pop(_state, 1);

		return res;
	}

	bool State::getReturnBool(void)
	{
		bool res = false;

		if (lua_isnil(_state, -1))
			return res;
		if (!lua_isboolean(_state, -1))
			return res;
		res = lua_toboolean(_state, -1);
		lua_pop(_state, 1);
		return res;
	}

	float State::getNumber(int idx)
	{
		return lua_tonumber(_state, idx);
	}

	const void *State::getPointer(int idx)
	{
		return lua_topointer(_state, idx);
	}

	int State::getFirstUpValueIdx(void)
	{
		return lua_upvalueindex(1);
	}

	bool State::callFunction(int nbParams, int nbReturns)
	{
		lua_pcall(_state, nbParams, nbReturns, 0);
		return true;
	}

	void State::setTable(void)
	{
		lua_settable(_state, -3);
	}

	void State::push(float val)
	{
		lua_pushnumber(_state, val);
	}

	void State::push(std::string str)
	{
		lua_pushstring(_state, str.c_str());
	}

	void State::newTable(void)
	{
		lua_newtable(_state);
	}

	void State::popLast(void)
	{
		lua_pop(_state, -1);
	}
}
