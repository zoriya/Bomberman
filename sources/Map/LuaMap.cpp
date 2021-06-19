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
		_player = Vector2f(pos.x, pos.z);
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
			if (_map[neighbor.y][neighbor.x] == 0 &&
				_danger[neighbor.y][neighbor.x] != 1)
				neighbors.push_back(neighbor);
		}
		if (neighbors.size())
			return neighbors;
		for (auto &dir : _dirs) {
			Vector2f neighbor(node.x + dir.x, node.y + dir.y);
			if (neighbor.y < 0 || neighbor.x < 0)
				continue;
			if (neighbor.y >= 17 || neighbor.x >= 17)
				continue;
			if (_map[neighbor.y][neighbor.x] == 0)
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
			[&fScore](const auto &l, const auto &r) -> bool
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

	Vector2f LuaMap::findSafeSpace(void) const
	{
		int d = 1;
		std::vector<std::vector<int>> distance(17, std::vector<int>(17, -1));
		std::vector<std::vector<int>> direction(17, std::vector<int>(17, -1));
		// -1 is empty, -2 is blocked
		for (int i = 0; i < 17; i++)
			for (int j = 0; j < 17; j++)
				distance[i][j] = _map[i][j] == 0 ? -1 : -2;
		distance[_roundedPlayer.y][_roundedPlayer.x] = 0;
		for (int i = 0; i < 4; i++) {
			Vector2f pos = _roundedPlayer + _dirs[i];
			if (pos.x < 0 || pos.x > 16 || pos.y < 0 || pos.y > 16)
				continue;
			distance[pos.y][pos.x] = 1;
			direction[pos.y][pos.x] = i;
		}
		int finalDir = -1;
		while (d < 6) {
			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 17; j++) {
					if (distance[j][i] != d)
						continue;
					auto currentDir = direction[j][i];

					for (int k = 0; k < 4; k++) {
						Vector2f pos = Vector2f(i, j) + _dirs[k];
						if (pos.x < 0 || pos.x > 16 || pos.y < 0 || pos.y > 16)
							continue;
						if (distance[pos.y][pos.x] != -1)
							continue;
						if (_danger[pos.y][pos.x] == 0)
							return _roundedPlayer + _dirs[currentDir];
						direction[pos.y][pos.x] = currentDir;
						distance[pos.y][pos.x] = d + 1;
					}
				}
			}
			d++;
		}
		return _roundedPlayer;
	}

	int LuaMap::getMap(lua_State *L)
	{
		LuaG::State state(L);
		int index = 1;
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		state.newTable();
		for (int i = 0; i < 17; i++) {
			state.push(index++);
			state.newTable();
			int indexrow = 1;
			for (int j = 0; j < 17; j++) {
				state.push(indexrow++);
				state.push(map->_map[i][j]);
				state.setTable();
			}
			state.setTable();
		}
		return 1;	
	}
	
	int LuaMap::getDanger(lua_State *L)
	{
		LuaG::State state(L);
		int index = 1;
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		state.newTable();
		for (int i = 0; i < 17; i++) {
			state.push(index++);
			state.newTable();
			int indexrow = 1;
			for (int j = 0; j < 17; j++) {
				state.push(indexrow++);
				state.push(map->_danger[i][j]);
				state.setTable();
			}
			state.setTable();
		}
		return 1;
	}
	
	int LuaMap::getPath(lua_State *L)
	{
		LuaG::State state(L);
		auto y2 = state.getNumber(-1);
		auto x2 = state.getNumber(-2);
		auto y1 = state.getNumber(-3);
		auto x1 = state.getNumber(-4);
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		Vector2f fst(x1, y1);
		Vector2f snd(x2, y2);
		auto path = map->pathfind(fst, snd);
		int index = 1;
		state.newTable();
		for (auto &r : path) {
			state.push(index++);
			state.newTable();
			state.push("x");
			state.push(r.x);
			state.setTable();
			state.push("y");
			state.push(r.y);
			state.setTable();
			state.setTable();
		}
		return 1;
	}

	int LuaMap::getPlayer(lua_State *L)
	{
		LuaG::State state(L);
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		state.newTable();
		state.push("x");
		state.push(map->_player.x);
		state.setTable();
		state.push("y");
		state.push(map->_player.y);
		state.setTable();
		return 1;
	}

	int LuaMap::getPlayerRound(lua_State *L)
	{
		LuaG::State state(L);
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		state.newTable();
		state.push("x");
		state.push(map->_roundedPlayer.x);
		state.setTable();
		state.push("y");
		state.push(map->_roundedPlayer.y);
		state.setTable();
		return 1;
	}

	int LuaMap::getClosestSafeSpace(lua_State *L)
	{
		LuaG::State state(L);
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		Vector2f closest = map->findSafeSpace();
		state.newTable();
		state.push("x");
		state.push(closest.x);
		state.setTable();
		state.push("y");
		state.push(closest.y);
		state.setTable();
		return 1;
	}

	int LuaMap::getDangerLevelPlayer(lua_State *L)
	{
		LuaG::State state(L);
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		lua_pushboolean(L, map->_danger[map->_roundedPlayer.y][map->_roundedPlayer.x] > 0);
		return 1;
	}

	int LuaMap::getDangerLevel(lua_State *L)
	{
		LuaG::State state(L);
		auto y = state.getNumber(-1);
		auto x = state.getNumber(-2);
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		state.push(map->_danger[y][x]);
		return 1;
	}

	int LuaMap::getBlockType(lua_State *L)
	{
		LuaG::State state(L);
		auto y = state.getNumber(-1);
		auto x = state.getNumber(-2);
    	const LuaMap *map = reinterpret_cast<const LuaMap *>(state.getPointer(state.getFirstUpValueIdx()));
		state.push(map->_map[y][x]);
		return 1;
	}
}