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

		scene->addEntity("Bottom Wall")
			.addComponent<PositionComponent>(Vector3f((width + 1) / 2, 0, -1))
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj), RAY::Vector3(width + 3, 1, 1));
		scene->addEntity("Upper Wall")
			.addComponent<PositionComponent>(Vector3f((width + 1) / 2, 0, height + 1))
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj), RAY::Vector3(width + 3, 1, 1));
		scene->addEntity("Left Wall")
			.addComponent<PositionComponent>(Vector3f(width + 1, 0, height / 2))
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj), RAY::Vector3(1, 1, height + 1));
		scene->addEntity("Right Wall")
			.addComponent<PositionComponent>(Vector3f(-1, 0, height / 2))
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>(UnbreakableObj, std::make_pair(MAP_DIFFUSE, UnbreakablePnj), RAY::Vector3(1, 1, height + 1));
	}

	void MapGenerator::generateFloor(MapBlock map, int width, int height, std::shared_ptr<WAL::Scene> scene)
	{	
		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				if (map[std::make_tuple(i, 0, j)] != HOLE && map[std::make_tuple(i, 0, j)] != BUMPER)
					scene->addEntity("Unbreakable Wall")
						.addComponent<PositionComponent>(Vector3f(i, -1, j))
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
			{FLOOR, &createFloor},
			{BUMPER, &createBumper},
			{STAIRS, &createStairs},
			{UPPERFLOOR, &createUpperFloor},
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
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/breakatble_wall.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/breakable_wall.png"));
	}

	void MapGenerator::createFloor(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Floor")
			.addComponent<PositionComponent>(Vector3f(coords))
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/floor.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/floor.png"));
	}

	void MapGenerator::createUpperFloor(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		scene->addEntity("Upper Floor")
			.addComponent<PositionComponent>(Vector3f(coords))
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/upper_floor.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/upper_floor.png"));
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
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/hole.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/hole.png"));
			/* .addComponent<CollisionComponent>([](WAL::Entity &other, const WAL::Entity &entity) {
				if (other.hasComponent<HealthComponent>()) {
					auto &health = other.getComponent<HealthComponent>();
					health.takeDmg(health.getHealthPoint());
				}
			}, [](WAL::Entity &other, const WAL::Entity &entity){}); */
	}

	void MapGenerator::createBumper(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{	
		std::cout << "Bumper Created" << std::endl;
		scene->addEntity("Bumper Block")
			.addComponent<PositionComponent>(Vector3f(coords.x, coords.y, coords.z))
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/bumper.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/bumper.png"));
			/* .addComponent<CollisionComponent>([](const WAL::Entity &entity, WAL::Entity &other) {
				if (other.hasComponent<MovableComponent>()) {
					auto &movable = other.getComponent<MovableComponent>();
					movable.addForce(Vector3f(0, 5, 0));
				}
			}); */
	}

	void MapGenerator::createStairs(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		std::cout << "Stairs Created" << std::endl;
		scene->addEntity("Stairs Block")
			.addComponent<PositionComponent>(coords)
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent<RAY3D::Model>>("assets/wall/stairs.obj", std::make_pair(MAP_DIFFUSE, "assets/wall/stairs.png"));
	}

	bool MapGenerator::isCloseToBlockType(std::map<std::tuple<int, int, int>, BlockType> map, int x, int y, int z, BlockType blockType)
	{
		return (map[std::make_tuple(x - 1, y, z)] == blockType ||
			map[std::make_tuple(x + 1, y, z)] == blockType ||
			map[std::make_tuple(x, y,  z + 1)] == blockType ||
			map[std::make_tuple(x, y, z - 1)] == blockType);
	}

	MapGenerator::BlockType MapGenerator::getRandomBlockType()
	{	
    	double rnd = static_cast<double>(std::rand())/RAND_MAX;
		
		if (rnd > 0.95)
			return HOLE;
		if (rnd > 0.25)
			return BREAKABLE;
    	return NOTHING;
	}

	MapGenerator::MapBlock MapGenerator::createHeight(MapBlock map, int width, int height)
	{
		//double rnd = static_cast<double>(std::rand())/RAND_MAX;

		double rnd = 1;

		std::cout << "Height rnd" << rnd << std::endl;
		if (rnd > 0.60) {
			std::cout << "Up border" << std::endl;
			for (int i = 0; i < width + 1; i++) {
				map[std::make_tuple(i, 1, height)] = map[std::make_tuple(i, 0, height)];
				map[std::make_tuple(i, 0, height)] = UPPERFLOOR;
				map[std::make_tuple(i, 1, 0)] = map[std::make_tuple(i, 0, 0)];
				map[std::make_tuple(i, 0, 0)] = UPPERFLOOR;
			}
			map[std::make_tuple(0, 0, height - 1)] = STAIRS;
			map[std::make_tuple(0, 0, 1)] = STAIRS;
			map[std::make_tuple(width, 0, height - 1)] = STAIRS;
			map[std::make_tuple(width, 0, 1)] = STAIRS;
			map[std::make_tuple(width / 2, 0, height - 1)] = BUMPER;
			map[std::make_tuple(width / 2, 0, 1)] = BUMPER;
		}
		if (rnd > 0.30) {
			std::cout << "Up center" << std::endl;
			for (int i = width / 2 - width / 4; i < width / 2 + width / 4 + 1; i++) {
				for (int j = height / 2 - height/4; j < height / 2 + height / 4 + 1; j++) {
					if (map[std::make_tuple(i, 0, j)] == FLOOR)
						continue;
					map[std::make_tuple(i, 1, j)] = map[std::make_tuple(i, 0, j)];
					map[std::make_tuple(i, 0, j)] = UPPERFLOOR;
				}
			}
			map[std::make_tuple(width / 2 - width / 8, 0, height / 2 + height / 4 + 1)] = STAIRS;
			map[std::make_tuple(width / 2 + width / 8, 0, height / 2 - height / 4 - 1)] = STAIRS;
			map[std::make_tuple(width / 2 - width / 4 - 1, 0, height / 2 - height / 8)] = STAIRS;
			map[std::make_tuple(width / 2 + width / 4 + 1, 0, height / 2 + height / 8)] = STAIRS;
		}
		return map;
	}

	MapGenerator::MapBlock MapGenerator::createSpawner(MapBlock map, int width, int height)
	{
		map[std::make_tuple(0, 0, 0)] = SPAWNER;
		map[std::make_tuple(width, 0, 0)] = SPAWNER;
		map[std::make_tuple(0, 0, height)] = SPAWNER;
		map[std::make_tuple(width, 0, height)] = SPAWNER;

		return map;
	}

	MapGenerator::MapBlock MapGenerator::cleanBreakable(MapBlock map, int width, int height)
	{
		for (int i = 0; i < width + 1; i++)
			for (int j = 0; j < height; j++) {
				if (map[std::make_tuple(i, 0, j)] == BREAKABLE && isCloseToBlockType(map, i, 0, j, STAIRS))
					map[std::make_tuple(i, 0, j)] = NOTHING;
				if (map[std::make_tuple(i, 0, j)] == BREAKABLE && map[std::make_tuple(i, -1, j)] == BUMPER)
					map[std::make_tuple(i, 0, j)] = NOTHING;
			}
		return (map);
	}

	MapGenerator::MapBlock MapGenerator::createMap(int width, int height)
	{
		MapBlock map;

		width = width % 2 ? width + 1 : width;
		height = height % 2 ? height + 1 : height;
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				map[std::make_tuple(i, 0, j)] = NOTHING;
		map = createSpawner(map, width, height);
		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				if (map[std::make_tuple(i, 0, j)] == SPAWNER)
					continue;
				if (isCloseToBlockType(map, i , 0, j, SPAWNER)) {
					map[std::make_tuple(i, 0, j)] = NOTHING;
				} else {
					map[std::make_tuple(i, 0, j)] = getRandomBlockType();
				}
				if (map[std::make_tuple(i, 0, j)] == UNBREAKABLE && isCloseToBlockType(map, i, 0, j, UNBREAKABLE))
					map[std::make_tuple(i, 0, j)] = BREAKABLE;
			}
		}
		for (int i = 0; i < width + 1; i++)
			for (int j = 0; j < height + 1; j++)
				if (!((i + 1) % 2) && !((j + 1) % 2))
					map[std::make_tuple(i, 0, j)] = UNBREAKABLE;
		map = createHeight(map, width, height);
		map = cleanBreakable(map, width, height);
		return (map);
	}

	void MapGenerator::loadMap(int width, int height, MapBlock map, std::shared_ptr<WAL::Scene> scene)
	{	
		generateWall(width, height, scene);
		generateFloor(map, width, height, scene);
		for (int x = 0; x < width + 1; x++)
			for (int z = 0; z < height + 1; z++)
				for (int y = 0; y < 1 + 1; y++)
					createElement(Vector3f(x, y, z), scene, map[std::make_tuple(x, y, z)]);
	}

} // namespace BBM