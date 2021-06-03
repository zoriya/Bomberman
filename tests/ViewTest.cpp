//
// Created by Zoe Roux on 6/3/21.
//

#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include "System/Movable/MovableSystem.hpp"
#include "System/Controllable/ControllableSystem.hpp"
#include <catch2/catch.hpp>
#include <Wal.hpp>
#include <Component/Controllable/ControllableComponent.hpp>

#define private public
#include <Component/Movable/MovableComponent.hpp>

using namespace WAL;
using namespace BBM;

TEST_CASE("View creation", "[View]")
{
	Scene scene;
	scene.addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<ControllableComponent>();
	scene.addEntity("Box")
		.addComponent<PositionComponent>();
	REQUIRE(scene.view<PositionComponent>().size() == 2);
	REQUIRE(scene.view<PositionComponent, ControllableComponent>().size() == 1);
	Entity &entity = *scene.getEntities().begin();
	Entity &firstView = *scene.view<PositionComponent, ControllableComponent>().entities.begin();
	REQUIRE(&entity == &firstView);
}