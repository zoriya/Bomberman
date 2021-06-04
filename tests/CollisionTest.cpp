//
// Created by Louis Auzuret on 5/31/21.
//

#include <catch2/catch.hpp>
#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "Component/Movable/MovableComponent.hpp"
#include "System/Movable/MovableSystem.hpp"
#include "System/Collision/CollisionSystem.hpp"
#include "Wal.hpp"

#define private public
#include "Component/Collision/CollisionComponent.hpp"

using namespace WAL;
using namespace BBM;


TEST_CASE("Collision test", "[Component][System]")
{
	Wal wal;
	CollisionSystem collision(wal);
	wal.scene = std::make_shared<Scene>();
	wal.scene->addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<CollisionComponent>([](Entity &actual, const Entity &) {
			try {
			auto &pos = actual.getComponent<PositionComponent>();
			pos.position.x = 1;
			pos.position.y = 1;
			pos.position.z = 1;
			} catch (std::exception &e) {};
		}, [](Entity &, const Entity &){}, 5.0);
	Entity &entity = wal.scene->getEntities().front();
	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<CollisionComponent>().bound.x = 5;
	entity.getComponent<CollisionComponent>().bound.y = 5;
	entity.getComponent<CollisionComponent>().bound.z = 5;

	collision.onUpdate(entity, std::chrono::nanoseconds(1));
	collision.onFixedUpdate(entity);
	REQUIRE(entity.getComponent<PositionComponent>().position.x == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.y == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.z == 0.0);
	
	wal.scene->addEntity("block")
		.addComponent<PositionComponent>(2,2,2)
		.addComponent<CollisionComponent>(1);
	Entity &player = wal.scene->getEntities().front();
	collision.onUpdate(entity, std::chrono::nanoseconds(1));
	REQUIRE(player.hasComponent(typeid(PositionComponent)));
	collision.onFixedUpdate(player);
	REQUIRE(wal.scene->getEntities().size() == 2);
	REQUIRE(player.hasComponent(typeid(PositionComponent)));
	REQUIRE(player.getComponent<PositionComponent>().position.x == 1.0);
	REQUIRE(player.getComponent<PositionComponent>().position.y == 1);
	REQUIRE(player.getComponent<PositionComponent>().position.z == 1);
}


TEST_CASE("Collsion test with movable", "[Component][System]")
{
	Wal wal;
	CollisionSystem collision(wal);
	MovableSystem movable(wal);
	wal.scene = std::make_shared<Scene>();
	wal.scene->addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<CollisionComponent>([](Entity &actual, const Entity &) {}, [](Entity &actual, const Entity &) {}, 5.0)
		.addComponent<MovableComponent>();
	
	wal.scene->addEntity("block")
		.addComponent<PositionComponent>(0, 0, 0)
		.addComponent<CollisionComponent>([](Entity &actual, const Entity &){}, [](Entity &actual, const Entity &) {
			try {
			auto &mov = actual.getComponent<MovableComponent>();
			mov.resetVelocity();
			} catch (std::exception &e) {};
		}, 1);
	Entity &entity = wal.scene->getEntities().front();
	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<CollisionComponent>().bound.x = 5;
	entity.getComponent<CollisionComponent>().bound.y = 5;
	entity.getComponent<CollisionComponent>().bound.z = 5;

	entity.getComponent<MovableComponent>().addForce({1, 1, 1});
	collision.onUpdate(entity, std::chrono::nanoseconds(1));
	collision.onFixedUpdate(entity);
	movable.onUpdate(entity, std::chrono::nanoseconds(1));
	movable.onFixedUpdate(entity);
	REQUIRE(entity.getComponent<PositionComponent>().position.x == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.y == 0.0);
	REQUIRE(entity.getComponent<PositionComponent>().position.z == 0.0);
}