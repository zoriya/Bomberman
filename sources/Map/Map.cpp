//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//

#include "Map.hpp"
#include <cmath>

namespace BBM
{
	void Map::generateWall(int width, int height, WAL::Scene &scene)
	{
		WAL::Entity entity("Unbreakable Block");
		
		entity.addComponent<PositionComponent>(Vector3f(0,0,0));
		scene.addEntity(entity);
	}

	void Map::generateFloor(int width, int height, WAL::Scene &scene)
	{
		WAL::Entity entity("Unbreakable Block");
		
		entity.addComponent<PositionComponent>(Vector3f(0,0,0));
		scene.addEntity(entity);
	}

	void Map::createElement(Vector3f coords, Vector3f size, WAL::Scene &scene, BlockType blockType)
	{
		std::map<BlockType, std::function<void (Vector3f coords, Vector3f size, WAL::Scene &)>> elements = {
			{BREAKABLE, &createBreakable},
			{UNBREAKABLE, &createUnbreakable},
			{HOLE, &createHole},
			{BUMPER, &createBumper},
			{STAIRS, &createStairs}
		};
		auto element = std::find(elements.begin(), elements.end(), blockType);

		if (element == elements.end())
			return;
		element->second(coords, size, scene);
	}

	void Map::createBreakable(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Breakable Block");
		
		entity.addComponent<PositionComponent>(coords);
		//entity.addComponent<HealthComponent>(1);
		scene.addEntity(entity);
	}

	void Map::createUnbreakable(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Unbreakable Block");
		
		entity.addComponent<PositionComponent>(coords);
		scene.addEntity(entity);
	}

	void Map::createHole(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Hole Block");
		
		entity.addComponent<PositionComponent>(coords);
		/* entity.addComponent<ColliderComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
			//En commentaire car manque le HealthComponent sur la branche (pour pas gêner au niveau des erreurs)
			if (other.hasComponent<HealthComponent>()) {
				auto &health = other.getComponent<HealthComponent>();
				health.takeDmg(health.getHealthPoint());
			}
		}); */
		scene.addEntity(entity);
	}

	void Map::createBumper(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Bumper Block");
		
		entity.addComponent<PositionComponent>(coords);
		/* entity.addComponent<ColliderComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
			if (other.hasComponent<MovableComponent>()) {
				auto &movable = other.getComponent<MovableComponent>();
				movable.addForce(Vector3f(0, 0, 5));
			}
		} */
		scene.addEntity(entity);
	}

	bool Map::isBlockCloseToPlayer(std::map<std::tuple<int, int>, BlockType> map, int x, int y)
	{
		if (map[std::make_tuple(x - 1, y)] == '*' ||
			map[std::make_tuple(x + 1, y)] == '*' ||
			map[std::make_tuple(x, y + 1)] == '*' ||
			map[std::make_tuple(x, y - 1)] == '*')
			return (true);
		return (false);
	}

	void Map::createStairs(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Stairs Block");
		
		entity.addComponent<PositionComponent>(coords);
		scene.addEntity(entity);
	}
	
	Map::BlockType Map::getRandomBlockType(int seed, int blockCreated)
	{
		return BlockType((seed * blockCreated) % (END - 1));
		//! @brief Which one is better ?
		//return static_cast<BlockType>((seed * blockCreated) % (END - 1));

	}

	void Map::generateMap(int width, int height, int seed, WAL::Scene &scene)
	{
		std::map<std::tuple<int, int>, BlockType> map;
		
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				map[std::make_tuple(i, j)] = NOTHING;
		for (int i = 0; i < 4; i++) {
			map[std::make_tuple(static_cast<int>(std::pow(seed, i)) % (width - 1) + 1,  \
				static_cast<int>(std::pow(seed * 0.7, i)) % (height - 1) + 1)] = SPAWNER;
		}
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < height - 1; j++) {
				if (isBlockCloseToPlayer(map, i , j)) {
					map[std::make_tuple(i, j)] = NOTHING;
				} else {
					map[std::make_tuple(i, j)] = getRandomBlockType(seed, i * width + j);
				}
			}
		}
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < height - 1; j++) {
				createElement(Vector3f(i, 0, j), Vector3f(50,50,50), scene, map[std::make_tuple(i, j)]);
			}
		}
	}

} // namespace BBM