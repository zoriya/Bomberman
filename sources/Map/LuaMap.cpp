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
	: _map(17, std::vector<int>(17, 0)), _danger(17, std::vector<int>(17, 0))
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
				std::cout << neighbor << std::endl;
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
}