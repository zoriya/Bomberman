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
			LuaState *_state;
		public:
		//! @brief ctor
		State();

		//! @brief dtor
		~State();

		//! @brief No copy constrructor
		State &State(State &) = delete;

		//! @brief No assign operator
		State &operator() = delete;

		//! @brief Get Lua state
		LuaState *getState(void);

		//! @brief Execute a file in this state
		void dofile(std::string filepath);
	
		//! @brief Execute a string in this state
		void dostring(std::string str);
	
	}
}