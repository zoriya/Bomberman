//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//

#include "map.hpp"

namespace BBM
{
	static void Map::generateWall(int width, int height, WAL::Scene &scene)
	{

	}

	static void Map::generateFloor(int width, int height, WAL::Scene &scene)
	{
		
	}

	static void Map::createElement(Vector3f coords, Vector3f size, WAL::Scene &scene, BlockType blockType)
	{
		std::map<BlockType, std::function<void (Vector3f coords, Vector3f size, WAL::Scene &)>> elements = {
			{BREAKABLE, &createBreakable},
			{UNBREAKABLE, &createUnbreakable},
			{HOLE, createHole},
			{BUMPER, createBumper},
			{STAIRS, createStairs}
		};
		
		for (auto element : elements)
			if (element.first == blockType)
				element.second(coords, size, scene);
	}

	static void Map::createBreakable(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Breakable Block");
		
		entity.addComponent<PositionComponent>(coords);
		//entity.addComponent<HealthComponent>(1);
		scene.addEntity(entity);
	}

	static void Map::createUnbreakable(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Unbreakable Block");
		
		entity.addComponent<PositionComponent>(coords);
		scene.addEntity(entity);
	}

	static void Map::createHole(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Hole Block");
		
		entity.addComponent<PositionComponent>(coords);
		entity.addComponent<ColliderComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
			//En commentaire car manque le HealthComponent sur la branche (pour pas gêner au niveau des erreurs)
			/* if (other.hasComponent<HealthComponent>()) {
				auto &health = other.getComponent<HealthComponent>();
				health.takeDmg(health.getHealthPoint());
			} */
		});
		scene.addEntity(entity);
	}

	static void Map::createBumper(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Bumper Block");
		
		entity.addComponent<PositionComponent>(coords);
		entity.addComponent<ColliderComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
			if (other.hasComponent<MovableComponent>()) {
				auto &movable = other.getComponent<MovableComponent>();
				movable.addForce(Vector3f(0, 0, 5));
			}
		}
		scene.addEntity(entity);
	}

	static bool Map::isBlockCloseToPlayer(std::map<std::tuple<int, int>, char> map, int x, int y)
	{
		if (map[x - 1, y] == '*' ||
			map[x + 1, y] == '*' ||
			map[x, y + 1] == '*' ||
			map[x, y - 1] == '*' ||)
			return (true)
		return (false)
	}

	static void Map::createStairs(Vector3f coords, Vector3f size, WAL::Scene &scene)
	{
		WAL::Entity entity("Stairs Block");
		
		entity.addComponent<PositionComponent>(coords);
		scene.addEntity(entity);
	}
	
	static BlockType Map::getRandomBlockType(int seed, int blockCreated)
	{	
		return ((seed * blockCreated) % (END - 1))
	}

	static char Map::enumToChar(BlockType blockType)
	{
		switch (blockType) {
			case BREAKABLE:
				return 'X';
			case UNBREAKABLE:
				return '#';
			case HOLE:
				return 'O';
			case BUMPER:
				return 'B';
			case STAIRS:
				return 'S';
			default:
				return ' ';
		}
	}

	static void Map::generateMap(int width, int height, int seed, WAL::Scene &scene)
	{
		std::map<std::tuple<int, int>, char> map;
		
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				map[std::make_tuple(i, j)] = ' '
		for (int i = 0; i < 4; i++)
			map[std::make_tuple((int)(std::pow(seed, i) % (width - 1) + 1),(int)(std::pow(seed * 0.7, i) % (height - 1) + 1)] = '*';
		for (int i = 1; i < width - 1; i++)
			for (int j = 1; j < height - 1; j++)
				if (isBlockCloseToPlayer(map[std::make_tuple(i, j)], i , j))
					map[std::make_tuple(i, j)] = ' ';
				else
					map[std::make_tuple(i, j)] = enumToChar(getRandomBlockType(seed, i * width + j)
	}

} // namespace BBM