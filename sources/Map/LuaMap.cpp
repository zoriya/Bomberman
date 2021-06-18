//
//
//

#include <algorithm>
#include <map>
#include <set>
#include "Map.hpp"
#include "LuaMap.hpp"

namespace BBM
{
	LuaMap::LuaMap()
	: _map(17, std::vector<int>(17, 0)), _danger(17, std::vector<int>(17, 0)),
	_player(), _roundedPlayer()
	{
	}

	LuaMap::~LuaMap()
	{ }

	void LuaMap::clearDanger(void)
	{
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 17; j++) {
				_danger[i][j] = 0;
			}
		}
	}

	bool LuaMap::setDanger(int xpos, int ypos, int dangerLevel)
	{
		if (xpos < 0 || xpos > 16 ||
			ypos < 0 || ypos > 16)
			return false;
		if (_map[ypos][xpos] == MapGenerator::BREAKABLE ||
			_map[ypos][xpos] == MapGenerator::UNBREAKABLE)
			return false;
		_danger[ypos][xpos] = dangerLevel;	
		return true;
	}

	void LuaMap::setPlayer(Vector3f pos)
	{
		_player = Vector2f(pos.x, pos.y);
		_roundedPlayer = Vector2f(std::round(_player.x), std::round(_player.y));
	}

	std::vector<Vector2f> LuaMap::fillPath(std::vector<Vector2f> &path, 
	std::unordered_map<Vector2f, Vector2f> &cameFrom, Vector2f node) const
	{
		if (cameFrom.find(node) != cameFrom.end()) {
			path.insert(path.begin(), cameFrom[node]);
			return fillPath(path, cameFrom, cameFrom[node]);
		} else
			return path;
	}

	std::vector<Vector2f> LuaMap::getNeighbors(Vector2f node) const
	{
		std::vector<Vector2f> neighbors;
		for (auto &dir : _dirs) {
			Vector2f neighbor(node.x + dir.x, node.y + dir.y);
			if (neighbor.y < 0 || neighbor.x < 0)
				continue;
			if (neighbor.y >= 17 || neighbor.x >= 17)
				continue;
			if (_map[neighbor.y][neighbor.x] <= 1 &&
				_danger[neighbor.y][neighbor.x] != 1)
				neighbors.push_back(neighbor);
		}
		return neighbors;
	}

	std::vector<Vector2f> LuaMap::pathfind(Vector2f root, Vector2f target) const
	{
		std::vector<Vector2f> closed;
		std::vector<Vector2f> open;
		std::unordered_map<Vector2f, Vector2f> cameFrom;
		std::unordered_map<Vector2f, double> gScore;
		std::unordered_map<Vector2f, double> fScore;
		std::vector<Vector2f> path;

		open.push_back(root);
		gScore[root] = 0;
		fScore[root] = root.distance(target);

		while (open.size())
		{
			auto min_elem = std::min_element(open.begin(), open.end(),
			[&fScore](const decltype(open)::value_type &l, const decltype(open)::value_type &r) -> bool
			{
				if (fScore.find(l) == fScore.end())
					return true;
				if (fScore.find(r) == fScore.end())
					return false;
				return fScore[l] < fScore[r];
			});
			if (min_elem == open.end())
				break;
			Vector2f current(*min_elem);
			if (current == target) {
				this->fillPath(path, cameFrom, target);
				path.push_back(target);
				return path;
			}
			open.erase(std::remove(open.begin(), open.end(), current), open.end());
			closed.push_back(current);
			auto neighbors = getNeighbors(current);
			for (auto &neighbor : neighbors) {
				if (std::find(closed.begin(), closed.end(), neighbor) != closed.end())
					continue;
				int tryGSCore = gScore[current] + 1;
				int GScoreNeighbor = 10000;
				if (gScore.find(neighbor) != gScore.end())
					GScoreNeighbor = gScore[neighbor];
				if (tryGSCore < GScoreNeighbor &&
					std::find(open.begin(), open.end(), neighbor) == open.end()) {
					cameFrom[neighbor] = current;
					gScore[neighbor] = tryGSCore;
					fScore[neighbor] = gScore[neighbor] + neighbor.distance(target);
					open.push_back(neighbor);
				}
			}
		}
		return path;
	}

	int LuaMap::getMap(lua_State *L)
	{
		LuaG::State state(L);
		int index = 1;
    	const LuaMap *map = (const LuaMap *) lua_topointer(L, lua_upvalueindex(1));
		lua_newtable(L);
		for (int i = 0; i < 17; i++) {
			lua_pushinteger(L, index++);
			lua_newtable(L);
			int indexrow = 1;
			for (int j = 0; j < 17; j++) {
				lua_pushinteger(L, indexrow++);
				lua_pushinteger(L, map->_map[i][j]);
				lua_settable(L, -3);
			}
			lua_settable(L, -3);
		}
		return 1;	
	}
	
	int LuaMap::getDanger(lua_State *L)
	{
		int index = 1;
    	const LuaMap *map = (const LuaMap *) lua_topointer(L, lua_upvalueindex(1));
		lua_newtable(L);
		for (int i = 0; i < 17; i++) {
			lua_pushinteger(L, index++);
			lua_newtable(L);
			int indexrow = 1;
			for (int j = 0; j < 17; j++) {
				lua_pushinteger(L, indexrow++);
				lua_pushinteger(L, map->_danger[i][j]);
				lua_settable(L, -3);
			}
			lua_settable(L, -3);
		}
		return 1;
	}
	
	int LuaMap::getPath(lua_State *L)
	{
		LuaG::State state(L);
		auto y2 = lua_tonumber(L, -1);
		auto x2 = lua_tonumber(L, -2);
		auto y1 = lua_tonumber(L, -3);
		auto x1 = lua_tonumber(L, -4);
    	const LuaMap *map = (const LuaMap *) lua_topointer(L, lua_upvalueindex(1));
		Vector2f fst(x1, y1);
		Vector2f snd(x2, y2);
		auto path = map->pathfind(fst, snd);
		int index = 1;
		lua_newtable(L);
		for (auto &r : path) {
			lua_pushinteger(L, index++);
			lua_newtable(L);
			lua_pushstring(L, "x");
			lua_pushnumber(L, r.x);
			lua_settable(L, -3);
			lua_pushstring(L, "y");
			lua_pushnumber(L, r.y);
			lua_settable(L, -3);
			lua_settable(L, -3);
		}
		return 1;
	}

	int LuaMap::getPlayer(lua_State *L)
	{
		LuaG::State state(L);
    	const LuaMap *map = (const LuaMap *) lua_topointer(L, lua_upvalueindex(1));
		lua_newtable(L);
		lua_pushstring(L, "x");
		lua_pushnumber(L, map->_player.x);
		lua_settable(L, -3);
		lua_pushstring(L, "y");
		lua_pushnumber(L, map->_player.y);
		lua_settable(L, -3);
		return 1;
	}

	int LuaMap::getPlayerRound(lua_State *L)
	{
		LuaG::State state(L);
    	const LuaMap *map = (const LuaMap *) lua_topointer(L, lua_upvalueindex(1));
		lua_newtable(L);
		lua_pushstring(L, "x");
		lua_pushnumber(L, map->_roundedPlayer.x);
		lua_settable(L, -3);
		lua_pushstring(L, "y");
		lua_pushnumber(L, map->_roundedPlayer.y);
		lua_settable(L, -3);
		return 1;
	}

	int LuaMap::getClosestSafeSpace(lua_State *L)
	{
		LuaG::State state(L);
    	const LuaMap *map = (const LuaMap *) lua_topointer(L, lua_upvalueindex(1));
		return 1;
	}
}