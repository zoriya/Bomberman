//
// Created by Zoe Roux on 5/31/21.
//

#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include <catch2/catch.hpp>
#include <Wal.hpp>

#define private public
#include "System/Controllable/ControllableSystem.hpp"
#include "System/Movable/MovableSystem.hpp"
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/Movable/MovableComponent.hpp>

using namespace WAL;
using namespace BBM;


TEST_CASE("Move test", "[Component][System]")
{
	Wal wal;
	Scene scene;
	scene.addEntity("player")
		.addComponent<ControllableComponent>()
		.addComponent<MovableComponent>()
		.addComponent<PositionComponent>();
	Entity &entity = *scene.getEntities().begin();

	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<ControllableComponent>().move = Vector2f(1, 1);

	ControllableSystem controllable(wal);
	controllable.onUpdate(entity, std::chrono::nanoseconds(1));
	controllable.onFixedUpdate(entity);
	REQUIRE(entity.getComponent<MovableComponent>()._acceleration.x > 0);
	REQUIRE(entity.getComponent<MovableComponent>()._acceleration.z > 0);

	MovableSystem movable(wal);
	movable.onUpdate(entity, std::chrono::nanoseconds(1));
	movable.onFixedUpdate(entity);
	REQUIRE(entity.getComponent<MovableComponent>()._velocity.x > 0);
	REQUIRE(entity.getComponent<MovableComponent>()._velocity.z > 0);
	REQUIRE(entity.getComponent<MovableComponent>()._acceleration.x == 0);
	REQUIRE(entity.getComponent<MovableComponent>()._acceleration.z == 0);
	movable.onUpdate(entity, std::chrono::nanoseconds(1));
	movable.onFixedUpdate(entity);
	REQUIRE(entity.getComponent<PositionComponent>().position.x > 0);
	REQUIRE(entity.getComponent<PositionComponent>().position.z > 0);

}