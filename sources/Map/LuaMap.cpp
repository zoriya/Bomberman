//
//
//

#include <map>
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

	std::vector<Vector2f> pathfind(Vector2f root, Vector2f target)
	{
		/*
		std::vector<Vector2f> closed;
		std::vector<Vector2f> open;
		std::map<Vector2f, Vector2f> came_from;
		std::map<Vector2f, double> g_score;
		std::map<Vector2f, double> f_score;
		std::vector<Vector2f> path;

		g_score[root] = 0;
		f_score[root] = root.distance(target);

		while (open.size())
		{
			Vector2f current = getLowestFScore();
			if (current == target) {
				fill_path();
				return path;
			}
			remove_from_closed(current);
			add_to_open(current);
			auto neighbors = getNeighbors(current);
			for (auto &neighbor : neighbors) {
				if (neighbor in closed)
					continue;
				
			}
		}
		return path;*/
	}
}