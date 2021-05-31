//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//

#include "Map.hpp"
#include <cmath>
#include <Model/Model.hpp>

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{
	void Map::generateWall(int width, int height, std::shared_ptr<WAL::Scene> scene)
	{
		for (int i = 0; i < width; i++) {
			scene->addEntity("Width Wall")
				.addComponent<PositionComponent>(Vector3f(i,0,height))
				.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
			scene->addEntity("Width Wall")
				.addComponent<PositionComponent>(Vector3f(i,0,0))
				.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
		}
		for (int i = 0; i < height; i++) {
			scene->addEntity("Height Wall")
				.addComponent<PositionComponent>(Vector3f(width,0,i))
				.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
			scene->addEntity("Height Wall")
				.addComponent<PositionComponent>(Vector3f(0,0,i))
				.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
		}
		scene->addEntity("Width Wall")
				.addComponent<PositionComponent>(Vector3f(width, 0,height))
				.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
	}

	void Map::generateFloor(int width, int height,  std::shared_ptr<WAL::Scene> scene)
	{
		/* RAY3D::Model model = RAY3D::Model("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
		
		model.setScale(RAY::Vector3(width, 0, height)); */
		for (int i = 1; i < width; i++) {
			for (int j = 1; j < height; j++) {
				scene->addEntity("Floor")
					.addComponent<PositionComponent>(Vector3f(i,-1,j))
					.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/floor.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/floor.png"));
			}
		}
				//.addComponent<Drawable3DComponent<RAY3D::Model>>(model);
	}

	void Map::createElement(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene, BlockType blockType)
	{
		if (blockType == BREAKABLE) {
			createBreakable(coords, size, scene);
		} else if (blockType == UNBREAKABLE) {
			createUnbreakable(coords, size, scene);
		}
		/* std::map<BlockType, std::function<void (Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> )>> elements = {
			{BREAKABLE, &Map::createBreakable},
			{UNBREAKABLE, &Map::createUnbreakable},
			{HOLE, &Map::createHole},
			{BUMPER, &Map::createBumper},
			{STAIRS, &Map::createStairs}
		};
		auto element = std::find(elements.begin(), elements.end(), blockType);

		if (element == elements.end())
			return;
		element->second(coords, size, scene); */
	}

	void Map::createBreakable(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Breakable Block")
			.addComponent<PositionComponent>(coords)
			//.addComponent<HealthComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/breakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/breakable_wall.png"));
			//.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/breakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/breakable_wall.png"));
	}

	void Map::createUnbreakable(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Unbreakable Block")
			.addComponent<PositionComponent>(coords)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
	}

	void Map::createHole(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Hole Block")
			.addComponent<PositionComponent>(coords)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/hole_block.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/hole_block.png"));
			/* .addComponent<ColliderComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
				if (other.hasComponent<HealthComponent>()) {
					auto &health = other.getComponent<HealthComponent>();
					health.takeDmg(health.getHealthPoint());
				}
			}); */
		WAL::Entity entity("");
	}

	void Map::createBumper(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Bumper Block")
			.addComponent<PositionComponent>(coords);
		/* 	.addComponent<ColliderComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
			if (other.hasComponent<MovableComponent>()) {
				auto &movable = other.getComponent<MovableComponent>();
				movable.addForce(Vector3f(0, 0, 5));
			}
		} */
	}

	void Map::createStairs(Vector3f coords, Vector3f size,  std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Stairs Block")
			.addComponent<PositionComponent>(coords);
	}

	bool Map::isBlockCloseToBlockType(std::map<std::tuple<int, int>, BlockType> map, int x, int y, BlockType blockType)
	{
		if (map[std::make_tuple(x - 1, y)] == blockType ||
			map[std::make_tuple(x + 1, y)] == blockType ||
			map[std::make_tuple(x, y + 1)] == blockType ||
			map[std::make_tuple(x, y - 1)] == blockType)
			return (true);
		return (false);
	}
	
	Map::BlockType Map::getRandomBlockType(int seed, int blockCreated)
	{
		return static_cast<BlockType>((seed * blockCreated * rand()) % (HOLE));
	}

	void Map::generateMap(int width, int height, int seed,  std::shared_ptr<WAL::Scene> scene)
	{
		std::map<std::tuple<int, int>, BlockType> map;
		
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				map[std::make_tuple(i, j)] = NOTHING;
		map[std::make_tuple(1, 1)] = SPAWNER;
		map[std::make_tuple(width - 1, 1)] = SPAWNER;
		map[std::make_tuple(1, height - 1)] = SPAWNER;
		map[std::make_tuple(width - 1, height - 1)] = SPAWNER;
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < height - 1; j++) {
				if (isBlockCloseToBlockType(map, i , j, SPAWNER)) {
					map[std::make_tuple(i, j)] = NOTHING;
				} else {
					map[std::make_tuple(i, j)] = getRandomBlockType(seed, i * width + j);
				}
				if (map[std::make_tuple(i, j)] != NOTHING && isBlockCloseToBlockType(map, i , j, UNBREAKABLE) && !isBlockCloseToBlockType(map, i , j, SPAWNER)) {
					map[std::make_tuple(i, j)] = BREAKABLE;
				}
			}
		}
		generateWall(width, height, scene);
		generateFloor(width, height, scene);
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < height - 1; j++) {
				createElement(Vector3f(i, 0, j), Vector3f(50,50,50), scene, map[std::make_tuple(i, j)]);
			}
		}
	}

} // namespace BBM