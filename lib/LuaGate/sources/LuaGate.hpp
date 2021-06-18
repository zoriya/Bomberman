//
// Created by Louis Auzuret on 10/06/21
//

#pragma once

#include <string>
#include <lua.hpp>

namespace LuaG
{
	class State
	{
		private:
			//! @brief Lua state
			lua_State *_state;

			//! @brief Should close the state at destruction
			bool _shouldClose;
		public:
		//! @brief ctor
		State();

		//! @brief ctor
		State(lua_State *L, bool shouldClose = false);


		//! @brief dtor
		~State();

		//! @brief No copy constrructor
		State(const State &) = delete;

		//! @brief No assign operator
		State &operator=(const State &) = delete;

		//! @brief Get Lua state
		lua_State *getState(void);

		//! @brief Get global value on top of the stack
		void getGlobal(std::string str);

		//! @brief Execute a file in this state
		void dofile(std::string filepath);
	
		//! @brief Execute a string in this state
		void dostring(std::string str);

		//! @brief Get return Number
		float getReturnNumber(void);

		//! @brief Get return Number
		bool getReturnBool(void);

		//! @brief call a lua function
		bool callFunction(int nbParams, int nbReturns);

		//! @brief setTable
		void setTable(void);

		//! @brief push a number onto the lua stack
		void push(float val);

		//! @brief push a string onto the lua stack
		void push(std::string str);

		//! @brief Creates a new table at the top of the stack
		void newTable(void);

		//! @brief Pop last value on the stack
		void popLast(void);
	};
}