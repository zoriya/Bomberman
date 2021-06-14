//
// Created by Louis Auzuret on 10/06/21
//

#include <string>
#include "lua.hpp"

namespace LuaG
{
	class State
	{
		private:
			//! @”rief Lua state
			lua_State *_state;
		public:
		//! @brief ctor
		State();

		//! @brief dtor
		~State();

		//! @brief No copy constrructor
		State(const State &) = delete;

		//! @brief No assign operator
		State &operator=(const State &) = delete;

		//! @brief Get Lua state
		lua_State *getState(void);

		//! @brief Execute a file in this state
		void dofile(std::string filepath);
	
		//! @brief Execute a string in this state
		void dostring(std::string str);

		//! @brief Get return Number
		float getReturnNumber(void);

		//! @brief Get return Number
		bool getReturnBool(void);

		//! @brief call a lua function
		bool callFunction(std::string funcName, int nbParams, int nbReturns);
	};
}