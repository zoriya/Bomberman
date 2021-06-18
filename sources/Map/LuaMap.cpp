//
//
//

#include <map>
#include "LuaMap.hpp"

namespace BBM
{
	LuaMap::LuaMap()
	: _map(17, std::vector<int>(17, 0)), _danger(17, std::vector<int>(17, 0))
	{
	}

	LuaMap::~LuaMap()
	{ }


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