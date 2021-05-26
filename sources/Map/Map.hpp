//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//

#include <cmath>
#include <Component/Component.hpp>
#include <Component/Collider/ColliderComponent.hpp>
#include <Component/Movable/MovableComponent.hpp>
#include <Scene/Scene.hpp>
#include <map>
#include <tuple>

namespace BBM
{

	class Map
	{
		private:
			//! @brief Enum of the block available.
			static enum BlockType {
				NOTHING = 0,
				BREAKABLE = 1,
				UNBREAKABLE = 2,
				HOLE = 3,
				BUMPER = 4,
				STAIRS = 5,
				END = 6
			}

			//! @param seed seed to generate random block type
			//! @param blockCreated block created since the beginning
			//! @brief Generate random block type
			static BlockType getRandomBlockType(int seed, int blockCreated);

			//! @param map ASCII map
			//! @param x x index on the block
			//! @param y y index on the block
			static bool isBlockCloseToPlayer(std::map<std::tuple<int, int>, char> map, int x, int y)

			//! @param width Width of the map
			//! @param height Height of the map
			//! @param scene Scene where the map is instanced
			//! @brief Generate the wall of the map
			static void generateWall(int width, int height, WAL::Scene &scene);

			//! @param width Width of the map
			//! @param height Height of the map
			//! @param scene Scene where the map is instanced
			//! @brief Generate the floor of the map
			static void generateFloor(int width, int height, WAL::Scene &scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create element of the map
			static void createElement(Vector3f coords, Vector3f size, WAL::Scene &scene, BlockType blockType);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create breakable of the map
			static void createBreakable(Vector3f coords, Vector3f size, WAL::Scene &scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create unbreakable of the map
			static void createUnbreakable(Vector3f coords, Vector3f size, WAL::Scene &scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create hole of the map
			static void createHole(Vector3f coords, Vector3f size, WAL::Scene &scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create bumper of the map
			static void createBumper(Vector3f coords, Vector3f size, WAL::Scene &scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create stair of the map
			static void createStairs(Vector3f coords, Vector3f size, WAL::Scene &scene);
			static char enumToChar(BlockType blockType);
		public:
			//! @param width Width of the map
			//! @param height Height of the map
			//! @param scene Scene where the map is instanced
			//! @brief Generate the map
			static void generateMap(int width, int height, int seed, WAL::Scene &scene);
			
	}
} // namespace BBM
