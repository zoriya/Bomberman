//
//
//

#pragma once
#include <lua.hpp>
#include "LuaGate.hpp"
#include "Models/Vector2.hpp"
#include <vector>

namespace BBM
{
	class LuaMap {
		public:
			//! @brief ctor
			LuaMap();

			//! @brief dtor
			~LuaMap();

			//! @brief Clear danger map
			void clearDanger(void);

			//! @brief set dangerlevel at xpos ypos
			bool setDanger(int xpos, int ypos, int dangerLevel);

			//! @brief set player position
			void setPlayer(Vector3f pos);

			//! @brief A star pathfinding between two points
			std::vector<Vector2f> pathfind(Vector2f, Vector2f) const;

			//! @brief find a safe space for current player
			Vector2f findSafeSpace(const std::vector<std::vector<int>> &dangerMap) const;

			//! @brief push table of table of the map
			static int getMap(lua_State *L);

			//! @brief push table of table of the danger map
			static int getDanger(lua_State *L);

			//! @brief get array of nodes, path from a to b
			static int getPath(lua_State *L);

			//! @brief get player pos
			static int getPlayer(lua_State *L);

			//! @brief get rounded player pos
			static int getPlayerRound(lua_State *L);

			//! @brief get closest safe space of player
			static int getClosestSafeSpace(lua_State *L);

			//! @brief get danger level of player
			static int getDangerLevelPlayer(lua_State *L);

			//! @brief is xpos ypos in danger
			static int getDangerLevel(lua_State *L);

			//! @brief get block type at x y
			static int getBlockType(lua_State *L);

			//! @brief Check if current player can put a bomb with an escape
			static int canPutBomb(lua_State *L);

			//! @brief Get current explosion radius of the player
			static int getRadius(lua_State *L);

			//! @brief Get enemies position
			static int getEnemies(lua_State *L);

			//! @brief Get enemies position rounded
			static int getEnemiesRound(lua_State *L);

			//! @brief map blocks in 2D grid
			std::vector<std::vector<int>> _map;

			//! @brief dangers in 2D grid
			std::vector<std::vector<int>> _danger;

			//! @brief player position
			Vector2f _player;

			//! @brief other players position
			std::vector<Vector2f> _enemies;

			//! @brief rounded player position
			Vector2f _roundedPlayer;

			//! @brief Explosion radius of current player
			int currRadius;
		private:
			//! @brief unwind path for a_star
			std::vector<Vector2f> fillPath(std::vector<Vector2f> &path, 
			std::unordered_map<Vector2f, Vector2f> &cameFrom, Vector2f node) const;

			//! @brief get neighbors of node for a_star
			std::vector<Vector2f> getNeighbors(Vector2f node) const;

			std::vector<Vector2f> _dirs = {
				Vector2f(1, 0), Vector2f(-1, 0), Vector2f(0, 1), Vector2f(0, -1)
			};

	};
}

namespace std
{
	template<>
	struct hash<BBM::Vector2f>
	{
		typedef BBM::Vector2f argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const &in) const
		{
			union {
				float vector[2];
				result_type hashed;
			} hasher;
			hasher.vector[0] = in.x;
			hasher.vector[1] = in.y;
			return hasher.hashed;
		}
	};
}
