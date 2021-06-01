//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//

#include "Map.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM
{	
	void MapGenerator::generateUnbreakableBlock(int width, int height, std::shared_ptr<WAL::Scene> scene)
	{
		std::string UnbreakableObj = "assets/wall/unbreakable_wall.obj";
		std::string UnbreakablePnj = "assets/wall/unbreakable_wall.png";

		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				if (!(i % 2) && !(j % 2)) {
					scene->addEntity("Unbreakable Wall")
						.addComponent<PositionComponent>(Vector3f(i, 0, j))
						//.addComponent<CollisionComponent>(1)
						.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj));
				}
			}
		}
	}

	void MapGenerator::generateWall(int width, int height, std::shared_ptr<WAL::Scene> scene)
	{
		std::string UnbreakableObj = "assets/wall/unbreakable_wall.obj";
		std::string UnbreakablePnj = "assets/wall/unbreakable_wall.png";

		for (int i = -1; i < width + 1; i++) {
			scene->addEntity("Vertical Wall")
				.addComponent<PositionComponent>(Vector3f(i, 0, height + 1))
				//.addComponent<CollisionComponent>(1)
				.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj));
			scene->addEntity("Vertical Wall")
				.addComponent<PositionComponent>(Vector3f(i, 0, -1))
				//.addComponent<CollisionComponent>(1)
				.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj));
		}
		for (int i = -1; i < height + 1; i++) {
			scene->addEntity("Horizontal Wall")
				.addComponent<PositionComponent>(Vector3f(width + 1, 0, i))
				//.addComponent<CollisionComponent>(1)
				.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj));
			scene->addEntity("Horizontal Wall")
				.addComponent<PositionComponent>(Vector3f(-1, 0, i))
				//.addComponent<CollisionComponent>(1)
				.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj));
		}
		scene->addEntity("Vertical Wall")
				.addComponent<PositionComponent>(Vector3f(width + 1, 0, height + 1))
				//.addComponent<CollisionComponent>(1)
				.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj));
	}

	void MapGenerator::generateFloor(int width, int height, std::shared_ptr<WAL::Scene> scene)
	{
		/* RAY3D::Model model = RAY3D::Model("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
		
		model.setScale(RAY::Vector3(width, 0, height)); */
		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				scene->addEntity("Floor")
					.addComponent<PositionComponent>(Vector3f(i,-1,j))
					//.addComponent<CollisionComponent>(1)
					.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/floor.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/floor.png"));
			}
		}
	}

	void MapGenerator::createElement(Vector3f coords, std::shared_ptr<WAL::Scene> scene, BlockType blockType)
	{
		std::map<BlockType, MapElem> elements = {
			{BREAKABLE, &createBreakable},
			{UNBREAKABLE, &createUnbreakable},
			{HOLE, &createHole},
			/* {BUMPER, &Map::createBumper},
			{STAIRS, &Map::createStairs} */
		};

		try {
			auto element = elements.at(blockType);
			element(coords, scene);
		} catch (std::exception const &err) {
			return;
		}
	}

	void MapGenerator::createBreakable(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Breakable Block")
			.addComponent<PositionComponent>(coords)
			.addComponent<HealthComponent>(1)
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/breakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/breakable_wall.png"));
	}

	void MapGenerator::createUnbreakable(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Unbreakable Block")
			.addComponent<PositionComponent>(coords)
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/unbreakable_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/unbreakable_wall.png"));
	}

	void MapGenerator::createHole(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Hole Block")
			.addComponent<PositionComponent>(Vector3f(coords.x, coords.y - 1, coords.z))
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/hole.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/hole.png"));
			/* .addComponent<ColliderComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
				if (other.hasComponent<HealthComponent>()) {
					auto &health = other.getComponent<HealthComponent>();
					health.takeDmg(health.getHealthPoint());
				}
			}); */
	}

	void MapGenerator::createBumper(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Bumper Block")
			.addComponent<PositionComponent>(coords)
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/bumper_block.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/bumper_block.png"));
		/* 	.addComponent<ColliderComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
			if (other.hasComponent<MovableComponent>()) {
				auto &movable = other.getComponent<MovableComponent>();
				movable.addForce(Vector3f(0, 5, 0));
			}
		} */
	}

	void MapGenerator::createStairs(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Stairs Block")
			.addComponent<PositionComponent>(coords)
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/stairs_block.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/stairs_block.png"));
	}

	bool MapGenerator::isCloseToBlockType(std::map<std::tuple<int, int>, BlockType> map, int x, int z, BlockType blockType)
	{
		return (map[std::make_tuple(x - 1, z)] == blockType ||
			map[std::make_tuple(x + 1, z)] == blockType ||
			map[std::make_tuple(x, z + 1)] == blockType ||
			map[std::make_tuple(x, z - 1)] == blockType);
	}
	
	MapGenerator::BlockType MapGenerator::getRandomBlockType()
	{	
    	double rnd = static_cast<double>(std::rand())/RAND_MAX;
		
		std::printf("%f\n", rnd);
		if (rnd > 0.95)
			return HOLE;
		if (rnd > 0.10)
			return BREAKABLE;
    	return NOTHING;
	}

	std::map<std::tuple<int, int>, MapGenerator::BlockType> MapGenerator::createMap(int width, int height)
	{
		std::map<std::tuple<int, int>, BlockType> map;

		width = width % 2 ? width + 1 : width;
		height = height % 2 ? height + 1 : height;
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				map[std::make_tuple(i, j)] = NOTHING;
		map[std::make_tuple(0, 0)] = SPAWNER;
		map[std::make_tuple(width, 0)] = SPAWNER;
		map[std::make_tuple(0, height)] = SPAWNER;
		map[std::make_tuple(width, height)] = SPAWNER;
		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				if (map[std::make_tuple(i, j)] == SPAWNER)
					continue;
				if (isCloseToBlockType(map, i , j, SPAWNER)) {
					map[std::make_tuple(i, j)] = NOTHING;
				} else {
					map[std::make_tuple(i, j)] = getRandomBlockType();
				}
				if (map[std::make_tuple(i, j)] == UNBREAKABLE && isCloseToBlockType(map, i, j, UNBREAKABLE))
					map[std::make_tuple(i, j)] = BREAKABLE;
			}
		}
		for (int i = 0; i < width + 1; i++)
			for (int j = 0; j < height + 1; j++)
				if (!((i + 1) % 2) && !((j + 1) % 2))
					map[std::make_tuple(i, j)] = UNBREAKABLE;
		return (map);
	}
	
	void MapGenerator::loadMap(int width, int height, std::map<std::tuple<int, int>, \
BlockType> map, std::shared_ptr<WAL::Scene> scene)
	{	
		generateWall(width, height, scene);
		generateFloor(width, height, scene);
		for (int i = 0; i < width + 1; i++)
			for (int j = 0; j < height + 1; j++)
				createElement(Vector3f(i, 0, j), scene, map[std::make_tuple(i, j)]);
	}

} // namespace BBM