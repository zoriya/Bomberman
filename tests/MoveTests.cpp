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
	wal.scene = std::make_shared<Scene>();
	wal.scene->addEntity("player")
		.addComponent<ControllableComponent>()
		.addComponent<MovableComponent>()
		.addComponent<PositionComponent>();
	Entity &entity = wal.scene->getEntities().front();

	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f());

	entity.getComponent<ControllableComponent>().move = Vector2f(1, 1);

	ControllableSystem controllable(wal);
	controllable.update(std::chrono::nanoseconds(1));
	controllable.fixedUpdate();
	REQUIRE(entity.getComponent<MovableComponent>()._acceleration.x > 0);
	REQUIRE(entity.getComponent<MovableComponent>()._acceleration.z > 0);

	MovableSystem movable(wal);
	movable.update(std::chrono::nanoseconds(1));
	movable.fixedUpdate();
	REQUIRE(entity.getComponent<MovableComponent>()._velocity.x > 0);
	REQUIRE(entity.getComponent<MovableComponent>()._velocity.z > 0);
	REQUIRE(entity.getComponent<MovableComponent>()._acceleration.x == 0);
	REQUIRE(entity.getComponent<MovableComponent>()._acceleration.z == 0);
	movable.update(std::chrono::nanoseconds(1));
	movable.fixedUpdate();
	REQUIRE(entity.getComponent<PositionComponent>().position.x > 0);
	REQUIRE(entity.getComponent<PositionComponent>().position.z > 0);

}