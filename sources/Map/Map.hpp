//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//


#pragma once

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <random>
#include <map>
#include <tuple>
#include <algorithm>
#include "Component/Renderer/Drawable3DComponent.hpp"
#include "Scene/Scene.hpp"
#include "Model/Model.hpp"
#include "Component/Component.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Health/HealthComponent.hpp"
#include "Component/Collision/CollisionComponent.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include <chrono>



namespace BBM
{

	class MapGenerator
	{
	public:
		//! @brief Enum of the block available.
		enum BlockType
		{
			NOTHING,
			BREAKABLE,
			HOLE,
			UPPERFLOOR,
			FLOOR,
			BUMPER,
			SPAWNER,
			UNBREAKABLE
		};

		using MapBlock = std::map<std::tuple<int, int, int>, BlockType>;

		static void wallCollided(WAL::Entity &entity,
		                         const WAL::Entity &wall,
		                         CollisionComponent::CollidedAxis collidedAxis);
		static void wallDestroyed(WAL::Entity &entity, WAL::Wal &wal);


		//! @param width Width of the map
		//! @param height Height of the map
		//! @brief Generate map of block to be loaded
		static MapBlock createMap(int width, int height);

		//! @param width Width of the map
		//! @param height Height of the map
		//! @param map Map to load with block declared inside
		//! @param scene Scene where the map is instanced
		//! @brief Generate the map
		static void loadMap(int width, int height, MapBlock map, const std::shared_ptr<WAL::Scene> &scene);
	private:

		using MapElem = std::function<void(Vector3f coords, std::shared_ptr<WAL::Scene> scene)>;

		//! @brief Generate random block type
		static BlockType getRandomBlockType();

		//! @param map ASCII map
		//! @param x x index on the block
		//! @param z z index on the block
		//! @param blockType blockType to compare with position
		static bool isCloseToBlockType(std::map<std::tuple<int, int, int>, BlockType> map,
		                               int x, int y, int z,
		                               BlockType blockType);

		//! @param width Width of the map
		//! @param height Height of the map
		//! @param scene Scene where the map is instanced
		//! @brief Generate the unbreakable block of the map
		static void generateUnbreakableBlock(int width, int height, std::shared_ptr<WAL::Scene> scene);

		//! @param width Width of the map
		//! @param height Height of the map
		//! @param scene Scene where the map is instanced
		//! @brief Generate the wall of the map
		static void generateWall(int width, int height, std::shared_ptr<WAL::Scene> scene);

		//! @param width Width of the map
		//! @param height Height of the map
		//! @param scene Scene where the map is instanced
		//! @brief Generate the floor of the map
		static void generateFloor(MapBlock map, int width, int height, std::shared_ptr<WAL::Scene> scene);

		//! @param coords coords of the element
		//! @param scene Scene where the map is instanced
		//! @brief Create element of the map
		static void createElement(Vector3f coords, std::shared_ptr<WAL::Scene> scene, BlockType blockType);

		//! @param coords coords of the element
		//! @param scene Scene where the map is instanced
		//! @brief Create breakable of the map
		static void createBreakable(Vector3f coords, std::shared_ptr<WAL::Scene> scene);

		//! @param coords coords of the element
		//! @param scene Scene where the map is instanced
		//! @brief Create unbreakable of the map
		static void createUnbreakable(Vector3f coords, std::shared_ptr<WAL::Scene> scene);

		//! @param coords coords of the element
		//! @param scene Scene where the map is instanced
		//! @brief Create hole of the map
		static void createHole(Vector3f coords, std::shared_ptr<WAL::Scene> scene);

		//! @param coords coords of the element
		//! @param scene Scene where the map is instanced
		//! @brief Create bumper of the map
		static void createBumper(Vector3f coords, std::shared_ptr<WAL::Scene> scene);

		//! @param coords coords of the element
		//! @param scene Scene where the map is instanced
		//! @brief Create floor of the map
		static void createFloor(Vector3f coords, std::shared_ptr<WAL::Scene> scene);

		//! @param coords coords of the element
		//! @param scene Scene where the map is instanced
		//! @brief Create upper floor of the map
		static void createUpperFloor(Vector3f coords, std::shared_ptr<WAL::Scene> scene);

		//! @param map Map to load with block declared inside
		//! @param width Width of the map
		//! @param height Height of the map
		//! @brief Generate map of block to be loaded
		static MapBlock createSpawner(MapBlock map, int width, int height);

		//! @param map Map to load with block declared inside
		//! @param width Width of the map
		//! @param height Height of the map
		//! @brief Generate height for the map
		static MapBlock createHeight(MapBlock map, int width, int height);

		//! @param map Map to load with block declared inside
		//! @param width Width of the map
		//! @param height Height of the map
		//! @brief Clean breakable on stairs, bumpers, etc..
		static MapBlock cleanBreakable(MapBlock map, int width, int height);


		static const std::string assetsPath;

		static const std::string wallAssetsPath;

		static const std::string imageExtension;

		static const std::string objExtension;

		static const std::string unbreakableWallPath;

		static const std::string breakableWallPath;

		static const std::string floorPath;

		static const std::string stairsPath;

		static const std::string bumperPath;

		static const std::string secondFloorPath;

		static const std::string holePath;

		static const std::string secondFloorHolePath;

	};
} // namespace BBM