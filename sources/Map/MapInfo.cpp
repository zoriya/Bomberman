//
// Created by Louis Auzuret 09/06/21
//

#include "MapInfo.hpp"

namespace BBM
{
	MapInfo::MapInfo(Vector3f pos, MapGenerator::BlockType type)
	: x(pos.x), y(pos.y), z(pos.z), type(type)
	{ }

	MapInfo::MapInfo(const MapInfo &other)
	: x(other.x), y(other.y), z(other.z), type(other.type)
	{ }

	MapInfo &MapInfo::operator=(MapInfo &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->type = other.type;
		return *this;
	}	
}