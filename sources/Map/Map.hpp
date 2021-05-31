//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//


#pragma once

#include <cmath>
#include <map>
#include <tuple>
#include <algorithm>
#include <Component/Renderer/Drawable3DComponent.hpp>
#include <System/Renderer/Renderer3DSystem.hpp>
#include <Scene/Scene.hpp>
#include <Component/Component.hpp>
//#include "Component/Collider/ColliderComponent.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Movable/MovableComponent.hpp"

namespace BBM
{

	class Map
	{
		private:
			//! @brief Enum of the block available.
			enum BlockType {
				NOTHING,
				BREAKABLE,
				UNBREAKABLE,
				HOLE,
				BUMPER,
				STAIRS,
				SPAWNER,
				END
			};

			//! @param seed seed to generate random block type
			//! @param blockCreated block created since the beginning
			//! @brief Generate random block type
			static BlockType getRandomBlockType(int seed, int blockCreated);

			//! @param map ASCII map
			//! @param x x index on the block
			//! @param y y index on the block
			//! @param blockType blockType to compare with position
			static bool isBlockCloseToBlockType(std::map<std::tuple<int, int>, BlockType> map, int x, int y, BlockType blockType);


			//! @param width Width of the map
			//! @param height Height of the map
			//! @param scene Scene where the map is instanced
			//! @brief Generate the wall of the map
			static void generateWall(int width, int height,  std::shared_ptr<WAL::Scene> scene);

			//! @param width Width of the map
			//! @param height Height of the map
			//! @param scene Scene where the map is instanced
			//! @brief Generate the floor of the map
			static void generateFloor(int width, int height,  std::shared_ptr<WAL::Scene> scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create element of the map
			static void createElement(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene, BlockType blockType);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create breakable of the map
			static void createBreakable(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create unbreakable of the map
			static void createUnbreakable(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create hole of the map
			static void createHole(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create bumper of the map
			static void createBumper(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene);

			//! @param coords coords of the element
			//! @param size size of the element
			//! @param scene Scene where the map is instanced
			//! @brief Create stair of the map
			static void createStairs(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene);
		public:
			//! @param width Width of the map
			//! @param height Height of the map
			//! @param scene Scene where the map is instanced
			//! @brief Generate the map
			static void generateMap(int width, int height, int seed,  std::shared_ptr<WAL::Scene> scene);
			
	};
} // namespace BBM