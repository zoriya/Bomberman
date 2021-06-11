//
// Created by Louis Auzuret on 10/06/21
//

#include "LuaGate.hpp"

namespace LuaG
{
	State::State()
	: _state(luaL_newstate())
	{
		luaL_openlibs(_state);
	}

	State::~State()
	{
		lua_close(_state);
	}

	LuaState *State::getState(void)
	{
		return _state;
	}

	void State::dofile(std::string filepath)
	{
        luaL_dofile(_state, filepath.c_str());
	}

	void State::dostring(std::string str)
	{
        luaL_dostring(_state, str.c_str());
	}
}