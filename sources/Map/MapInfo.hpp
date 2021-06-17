//
// Created by Louis Auzuret on 09/06/21
//

#include "Map.hpp"

namespace BBM
{
	class MapInfo
	{
		private:
		public:
			//! @brief Position on the x axis
			float x;

			//! @brief Position on the y axis
			float y;

			//! @brief Position on the z axis
			float z;
			
			//! @brief Type of the block
			int type;

			//! @brief Constructor
			MapInfo(Vector3f pos, MapGenerator::BlockType type);

			//! @brief Default destructor
			~MapInfo() = default;

			//! @brief Default copy constructor
			MapInfo(const MapInfo &);

			//! @brief Assignment operator
			MapInfo &operator=(MapInfo &);
	};
}