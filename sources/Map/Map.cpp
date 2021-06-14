//
// Created by Tom Augier on 5/26/21.
// Edited by Benjamin Henry on 5/26/21.
//

#include "Component/Collision/CollisionComponent.hpp"
#include "System/Collision/CollisionSystem.hpp"
#include "Map.hpp"
#include <iostream>
#include <Items/Bonus.hpp>
#include <Component/Levitate/LevitateComponent.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include <Component/Tag/TagComponent.hpp>
#include <Component/BumperTimer/BumperTimerComponent.hpp>

namespace RAY3D = RAY::Drawables::Drawables3D;
using namespace std::chrono_literals;

namespace BBM
{
	void MapGenerator::bumperCollide(WAL::Entity &entity,
	                                 const WAL::Entity &wall,
	                                 CollisionComponent::CollidedAxis collidedAxis)
	{
		auto *movable = entity.tryGetComponent<MovableComponent>();
		auto *bumperTimer = entity.tryGetComponent<BumperTimerComponent>();

		if (!movable || !bumperTimer)
			return;
		if (!bumperTimer->_isReseting) {
			movable->_velocity.y = 1.5;
			bumperTimer->_isReseting = true;
		}
	}

	void MapGenerator::holeCollide(WAL::Entity &entity,
	                               const WAL::Entity &wall,
	                               CollisionComponent::CollidedAxis collidedAxis)
	{
		auto *health = entity.tryGetComponent<HealthComponent>();

		if (!health)
			return;
		health->takeDmg(health->getHealthPoint());
	}

	void MapGenerator::wallCollided(WAL::Entity &entity,
	                                const WAL::Entity &wall,
	                                CollisionComponent::CollidedAxis collidedAxis)
	{
		auto *mov = entity.tryGetComponent<MovableComponent>();

		if (!mov)
			return;
		if (collidedAxis & CollisionComponent::CollidedAxis::X)
			mov->_velocity.x = 0;
		if (collidedAxis & CollisionComponent::CollidedAxis::Y)
			mov->_velocity.y = 0;
		if (collidedAxis & CollisionComponent::CollidedAxis::Z)
			mov->_velocity.z = 0;
	}

	void MapGenerator::wallDestroyed(WAL::Entity &entity, WAL::Wal &wal)
	{
		entity.scheduleDeletion();
		auto &position = entity.getComponent<PositionComponent>().position;
		static std::map<Bonus::BonusType, std::string> map = {
				{Bonus::BonusType::BOMBSTOCK, "assets/items/bombup"},
				{Bonus::BonusType::SPEEDUP, "assets/items/speedup"},
				{Bonus::BonusType::EXPLOSIONINC, "assets/items/fireup"}
		};
		static std::vector<std::function<void (WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis)>> func = {
				&Bonus::BombUpBonus, &Bonus::SpeedUpBonus, &Bonus::ExplosionRangeBonus
		};
		auto bonusType = Bonus::getRandomBonusType();

		if (bonusType == Bonus::BonusType::NOTHING)
			return;
		if (!map.contains(bonusType))
			return;
		wal.getScene()->scheduleNewEntity("Bonus")
			.addComponent<PositionComponent>(position)
			.addComponent<TagComponent<Blowable>>()
			.addComponent<HealthComponent>(1, [](WAL::Entity &entity, WAL::Wal &wal) {
				entity.scheduleDeletion();
			})
			.addComponent<LevitateComponent>(position.y)
			.addComponent<CollisionComponent>([](WAL::Entity &bonus, const WAL::Entity &player, CollisionComponent::CollidedAxis axis) {
				bonus.scheduleDeletion();
			}, func[bonusType - 1], 0.5, .5)
			.addComponent<TimerComponent>(5s, [](WAL::Entity &bonus, WAL::Wal &wal){
				bonus.scheduleDeletion();
			})
			.addComponent<Drawable3DComponent, RAY3D::Model>(map.at(bonusType) + ".obj", false,
															 std::make_pair(MAP_DIFFUSE, "assets/items/items.png"));
	}

	const std::string MapGenerator::assetsPath = "./assets/";
	const std::string MapGenerator::wallAssetsPath = MapGenerator::assetsPath + "map/";
	const std::string MapGenerator::imageExtension = ".png";
	const std::string MapGenerator::objExtension = ".obj";
	const std::string MapGenerator::breakableWallPath = MapGenerator::wallAssetsPath + "breakable_wall";
	const std::string MapGenerator::unbreakableWallPath = MapGenerator::wallAssetsPath + "unbreakable_wall";
	const std::string MapGenerator::floorPath = MapGenerator::wallAssetsPath + "floor";
	const std::string MapGenerator::secondFloorPath = MapGenerator::wallAssetsPath + "upper_floor";
	const std::string MapGenerator::stairsPath = MapGenerator::wallAssetsPath + "stairs";
	const std::string MapGenerator::bumperPath = MapGenerator::wallAssetsPath + "bumper";
	const std::string MapGenerator::holePath = MapGenerator::wallAssetsPath + "hole";
	const std::string MapGenerator::secondFloorHolePath = MapGenerator::secondFloorPath + "_hole";

	void MapGenerator::generateUnbreakableBlock(int width, int height, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string unbreakableObj = unbreakableWallPath + objExtension;
		static const std::string unbreakablePng = unbreakableWallPath + imageExtension;

		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				if (!(i % 2) && !(j % 2)) {
					scene->addEntity("Unbreakable Wall")
						.addComponent<PositionComponent>(i, 0, j)
						.addComponent<TagComponent<Blowable>>()
						.addComponent<CollisionComponent>(
							WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
							&MapGenerator::wallCollided, 0.25, .75)
						.addComponent<Drawable3DComponent, RAY3D::Model>(unbreakableObj, false,
						                                                 std::make_pair(MAP_DIFFUSE, unbreakablePng));
				}
			}
		}
	}

	void MapGenerator::generateWall(int width, int height, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string unbreakableObj = unbreakableWallPath + objExtension;
		static const std::string unbreakablePnj = unbreakableWallPath + imageExtension;

		for (int i = 0; i < height; i++) {
			scene->addEntity("Bomb stopper")
				.addComponent<PositionComponent>(-1, 0, i)
				.addComponent<TagComponent<Blowable>>();
			scene->addEntity("Bomb stopper")
				.addComponent<PositionComponent>(width + 1, 0, i)
				.addComponent<TagComponent<Blowable>>();
		}
		for (int i = 0; i < width; i++) {
			scene->addEntity("Bomb stopper")
				.addComponent<PositionComponent>(i, 0, -1)
				.addComponent<TagComponent<Blowable>>();
			scene->addEntity("Bomb stopper")
				.addComponent<PositionComponent>(i, 0, height + 1)
				.addComponent<TagComponent<Blowable>>();
		}

		scene->addEntity("Bottom Wall")
			.addComponent<PositionComponent>(Vector3f((width + 1) / 2, 0, -1))
			.addComponent<CollisionComponent>(
				WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
				&MapGenerator::wallCollided, Vector3f(-(width + 1) / 2 , 0.25, 0.25), Vector3f(width + 1, 2, 0.75))
			.addComponent<Drawable3DComponent, RAY3D::Model>(unbreakableObj, false,
			                                                 std::make_pair(MAP_DIFFUSE, unbreakablePnj),
			                                                 RAY::Vector3(width + 3, 1, 1));
		scene->addEntity("Upper Wall")
			.addComponent<PositionComponent>(Vector3f((width + 1) / 2, 0, height + 1))
			.addComponent<CollisionComponent>(
				WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
				&MapGenerator::wallCollided, Vector3f(-(width + 1) / 2 , 0.25, 0.25), Vector3f(width + 1, 2, 0.75))
			.addComponent<Drawable3DComponent, RAY3D::Model>(unbreakableObj, false,
			                                                 std::make_pair(MAP_DIFFUSE, unbreakablePnj),
			                                                 RAY::Vector3(width + 3, 1, 1));
		scene->addEntity("Left Wall")
			.addComponent<PositionComponent>(Vector3f(width + 1, 0, height / 2))
			.addComponent<CollisionComponent>(
				WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
				&MapGenerator::wallCollided, Vector3f(0.25, 0.25, -(height + 1) / 2 ), Vector3f(0.75, 2, height + 1))
			.addComponent<Drawable3DComponent, RAY3D::Model>(unbreakableObj, false,
			                                                 std::make_pair(MAP_DIFFUSE, unbreakablePnj),
			                                                 RAY::Vector3(1, 1, height + 1));
		scene->addEntity("Right Wall")
			.addComponent<PositionComponent>(Vector3f(-1, 0, height / 2))
			.addComponent<CollisionComponent>(
				WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
				&MapGenerator::wallCollided, Vector3f(0.25, 0.25, -(height + 1) / 2 ), Vector3f(0.75, 2, height + 1))
			.addComponent<Drawable3DComponent, RAY3D::Model>(unbreakableObj, false,
			                                                 std::make_pair(MAP_DIFFUSE, unbreakablePnj),
			                                                 RAY::Vector3(1, 1, height + 1));
	}

	void MapGenerator::generateFloor(MapBlock map, int width, int height, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string floorObj = floorPath + objExtension;
		static const std::string floorPng = floorPath + imageExtension;

		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				if (map[std::make_tuple(i, 0, j)] != HOLE && map[std::make_tuple(i, -1, j)] != BUMPER)
					scene->addEntity("Unbreakable Wall")
						.addComponent<PositionComponent>(Vector3f(i, -1, j))
						.addComponent<Drawable3DComponent, RAY3D::Model>(floorObj, false,
						                                                 std::make_pair(MAP_DIFFUSE, floorPng));
			}
		}
	}

	void MapGenerator::createElement(Vector3f coords, std::shared_ptr<WAL::Scene> scene, BlockType blockType)
	{
		std::map<BlockType, MapElem> elements = {
			{BREAKABLE,   &createBreakable},
			{UNBREAKABLE, &createUnbreakable},
			{HOLE,        &createHole},
			{FLOOR,       &createFloor},
			{BUMPER,      &createBumper},
			{UPPERFLOOR,  &createUpperFloor},
		};

		if (blockType == NOTHING || blockType == SPAWNER)
			return;
		auto element = elements.at(blockType);
		element(coords, std::move(scene));
	}

	void MapGenerator::createBreakable(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string breakableObj = breakableWallPath + objExtension;
		static const std::string breakablePng = breakableWallPath + imageExtension;

		scene->addEntity("Breakable Block")
			.addComponent<PositionComponent>(coords)
			.addComponent<TagComponent<Blowable>>()
			.addComponent<HealthComponent>(1, &MapGenerator::wallDestroyed)
			.addComponent<CollisionComponent>(
				WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
				&MapGenerator::wallCollided, 0.25, .75)
			.addComponent<Drawable3DComponent, RAY3D::Model>(breakableObj, false, std::make_pair(MAP_DIFFUSE, breakablePng));
	}

	void MapGenerator::createFloor(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string floorObj = floorPath + objExtension;
		static const std::string floorPng = floorPath + imageExtension;

		scene->addEntity("Floor")
			.addComponent<PositionComponent>(Vector3f(coords))
			//.addComponent<CollisionComponent>(1)
			.addComponent<Drawable3DComponent, RAY3D::Model>(floorObj, false, std::make_pair(MAP_DIFFUSE, floorPng));
	}

	void MapGenerator::createUpperFloor(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string floorObj = secondFloorPath + objExtension;
		static const std::string floorPng = secondFloorPath + imageExtension;

		scene->addEntity("Upper Floor")
			.addComponent<PositionComponent>(Vector3f(coords))
			.addComponent<Drawable3DComponent, RAY3D::Model>(floorObj, false, std::make_pair(MAP_DIFFUSE, floorPng));
	}


	void MapGenerator::createUnbreakable(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string UnbreakableObj = unbreakableWallPath + objExtension;
		static const std::string UnbreakablePng = unbreakableWallPath + imageExtension;

		scene->addEntity("Unbreakable Block")
			.addComponent<PositionComponent>(coords)
			.addComponent<TagComponent<Blowable>>()
			.addComponent<CollisionComponent>(
				WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
				&MapGenerator::wallCollided, 0.25, .75)
			.addComponent<Drawable3DComponent, RAY3D::Model>(UnbreakableObj, false,
			                                                 std::make_pair(MAP_DIFFUSE, UnbreakablePng));
	}

	void MapGenerator::createHole(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string holeObj = holePath + objExtension;
		static const std::string holePng = holePath + imageExtension;
		static const std::string secondFloorObj = secondFloorHolePath + objExtension;
		static const std::string secondFloorPng = secondFloorHolePath + imageExtension;

		WAL::Entity &holeEntity = scene->addEntity("Hole Block");

		holeEntity.addComponent<PositionComponent>(Vector3f(coords.x, coords.y - 1, coords.z))
	              .addComponent<CollisionComponent>(
		            WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
		            &MapGenerator::holeCollide, Vector3f(0.25, 0.25, 0.25),Vector3f(0.75, 1.75, 0.75));
		if (coords.y == 0)
			holeEntity.addComponent<Drawable3DComponent, RAY3D::Model>(holeObj, false, std::make_pair(MAP_DIFFUSE, holePng));
		else
			holeEntity.addComponent<Drawable3DComponent, RAY3D::Model>(secondFloorObj, false,
			                                                           std::make_pair(MAP_DIFFUSE, secondFloorPng));
		
	}

	void MapGenerator::createBumper(Vector3f coords, std::shared_ptr<WAL::Scene> scene)
	{
		static const std::string bumperObj = bumperPath + objExtension;
		static const std::string bumperPng = bumperPath + imageExtension;

		scene->addEntity("Bumper Block")
			.addComponent<PositionComponent>(Vector3f(coords.x, coords.y, coords.z))
			.addComponent<Drawable3DComponent, RAY3D::Model>(bumperObj, false,std::make_pair(MAP_DIFFUSE, bumperPng))
			.addComponent<CollisionComponent>(
		            WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
		            &MapGenerator::bumperCollide, Vector3f(0.25, 0.25, 0.25),Vector3f(0.75, 0.75, 0.75));
	}

	bool MapGenerator::isCloseToBlockType(std::map<std::tuple<int, int, int>, BlockType> map, int x, int y, int z,
	                                      BlockType blockType)
	{
		return (map[std::make_tuple(x - 1, y, z)] == blockType ||
		        map[std::make_tuple(x + 1, y, z)] == blockType ||
		        map[std::make_tuple(x, y, z + 1)] == blockType ||
		        map[std::make_tuple(x, y, z - 1)] == blockType);
	}

	MapGenerator::BlockType MapGenerator::getRandomBlockType()
	{
		double rnd = static_cast<double>(std::rand()) / RAND_MAX;

		if (rnd > 0.98)
			return HOLE;
		if (rnd > 0.25)
			return NOTHING;
		return NOTHING;
	}

	MapGenerator::MapBlock MapGenerator::createHeight(MapBlock map, int width, int height)
	{
		double rnd = static_cast<double>(std::rand()) / RAND_MAX;

		if (rnd > 0.01) {
			for (int i = 0; i < width + 1; i++) {
				map[std::make_tuple(i, 1, height)] = map[std::make_tuple(i, 0, height)];
				map[std::make_tuple(i, 0, height)] = UPPERFLOOR;
				map[std::make_tuple(i, 1, 0)] = map[std::make_tuple(i, 0, 0)];
				map[std::make_tuple(i, 0, 0)] = UPPERFLOOR;
			}
			map[std::make_tuple(0, -1, height - 1)] = BUMPER;
			map[std::make_tuple(0, -1, 1)] = BUMPER;
			map[std::make_tuple(width, -1, height - 1)] = BUMPER;
			map[std::make_tuple(width, -1, 1)] = BUMPER;
			map[std::make_tuple(width / 2, -1, height - 1)] = BUMPER;
			map[std::make_tuple(width / 2, -1, 1)] = BUMPER;
		} 
		if (rnd > 0.01) {
			for (int i = width / 2 - width / 4; i < width / 2 + width / 4 + 1; i++) {
				for (int j = height / 2 - height / 4; j < height / 2 + height / 4 + 1; j++) {
					map[std::make_tuple(i, 1, j)] = map[std::make_tuple(i, 0, j)];
					map[std::make_tuple(i, 0, j)] = UPPERFLOOR;
				}
			}
			map[std::make_tuple(width / 2 - width / 8, -1, height / 2 + height / 4 + 1)] = BUMPER;
			map[std::make_tuple(width / 2 + width / 8, -1, height / 2 - height / 4 - 1)] = BUMPER;
			map[std::make_tuple(width / 2 - width / 4 - 1, -1, height / 2 - height / 8)] = BUMPER;
			map[std::make_tuple(width / 2 + width / 4 + 1, -1, height / 2 + height / 8)] = BUMPER;
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
				if (map[std::make_tuple(i, 0, j)] == BREAKABLE && map[std::make_tuple(i, -1, j)] == BUMPER)
					map[std::make_tuple(i, 0, j)] = NOTHING;
				if (map[std::make_tuple(i, 1, j)] == BREAKABLE && isCloseToBlockType(map, i, -1, j, BUMPER))
					map[std::make_tuple(i, 1, j)] = NOTHING;
			}
		return (map);
	}

	MapGenerator::MapBlock MapGenerator::createClassicUnbreakable(MapBlock map, int width, int height)
	{
		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				if (!((i + 1) % 2) && !((j + 1) % 2))
					map[std::make_tuple(i, 0, j)] = UNBREAKABLE;
			}
		}
		return (map);
	}

	MapGenerator::MapBlock MapGenerator::createLongClassicUnbreakable(MapBlock map, int width, int height)
	{
		int placedSpace = 0;

		for (int i = 1; i < width; i++) {
			placedSpace = 0;
			for (int j = 1; j < height; j++) {
				if (!(j % 2))
					continue;
				if (i < (width / 2 - width / 10) || i > (width / 2 + width / 10))
					map[std::make_tuple(i, 0, j)] = UNBREAKABLE;
				else
					placedSpace++;
			}
		}
		return (map);
	}


	MapGenerator::MapBlock MapGenerator::createMap(int width, int height, bool isHeight, bool isNotClassic)
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
				if (isCloseToBlockType(map, i, 0, j, SPAWNER)) {
					map[std::make_tuple(i, isNotClassic ? -1 : 0, j)] = isNotClassic ? BUMPER : NOTHING;
				} else {
					map[std::make_tuple(i, 0, j)] = getRandomBlockType();
				}
				if (map[std::make_tuple(i, 0, j)] == UNBREAKABLE && isCloseToBlockType(map, i, 0, j, UNBREAKABLE))
					map[std::make_tuple(i, 0, j)] = BREAKABLE;
			}
		}
		if (!isNotClassic)
			map = createClassicUnbreakable(map, width, height);
		else
			map = createLongClassicUnbreakable(map, width, height);
		if (isHeight)
			map = createHeight(map, width, height);
		map = cleanBreakable(map, width, height);
		return (map);
	}

	void MapGenerator::generateHeightCollision(MapBlock map, int width, int height, std::shared_ptr<WAL::Scene> scene)
	{	
		int floor = 2;

		for (int i = 0; i < width + 1; i++) {
			if (map[std::make_tuple(i, 1, height)] != UPPERFLOOR && map[std::make_tuple(i, 1, height)] != UPPERFLOOR) {
				floor -= 1;
				break;
			}
		}
		for (int i = width / 2 - width / 4; i < width / 2 + width / 4 + 1; i++) {
			for (int j = height / 2 - height / 4; j < height / 2 + height / 4 + 1; j++) {
				if (map[std::make_tuple(i, 1, i)] != UPPERFLOOR) {
					floor -= 1;
					break;
				}
			}
			if (floor <= 0)
				break;
		}
		if (floor >= 1) {
			scene->addEntity("FloorBot Hitbox")
			.addComponent<PositionComponent>(Vector3f(0, 0, 0))
			.addComponent<CollisionComponent>(
				WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
				&MapGenerator::wallCollided, Vector3f(0.25, 0.25, 0.25), Vector3f(width, 0.75, 0.75));
			scene->addEntity("FloorUp Hitbox")
				.addComponent<PositionComponent>(Vector3f(0, 0, height))
				.addComponent<CollisionComponent>(
					WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
		            &MapGenerator::wallCollided, Vector3f(0.25, 0.25, 0.25),Vector3f(width, 0.75, 0.75));
		}
		if (floor >= 2)
			scene->addEntity("Middle Hitbox")
				.addComponent<PositionComponent>(Vector3f(width / 2 - width / 4, 0, height / 2 - height / 4))
				.addComponent<CollisionComponent>(
					WAL::Callback<WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis>(),
		            &MapGenerator::wallCollided, Vector3f(0.25, 0.25, 0.25),Vector3f(width, 0.75, height / 2 + height / 4));
	}

	void MapGenerator::loadMap(int width, int height, MapBlock map, const std::shared_ptr<WAL::Scene> &scene)
	{	
		generateHeightCollision(map, width, height, scene);
		generateWall(width, height, scene);
		generateFloor(map, width, height, scene);
		for (int x = 0; x < width + 1; x++)
			for (int z = 0; z < height + 1; z++)
				for (int y = -1; y < 1 + 1; y++)
					createElement(Vector3f(x, y, z), scene, map[std::make_tuple(x, y, z)]);
	}

} // namespace BBM