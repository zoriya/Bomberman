//
// Created by Zoe Roux on 6/3/21.
//

#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include <catch2/catch.hpp>
#include <Wal.hpp>
#include <Component/Controllable/ControllableComponent.hpp>

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

TEST_CASE("View update", "[View]")
{
	Scene scene;
	scene.addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<ControllableComponent>();
	auto &view = scene.view<PositionComponent>();
	auto &entity = scene.addEntity("Box")
		.addComponent<PositionComponent>();
	REQUIRE(view.size() == 2);
	entity.removeComponent<PositionComponent>();
	REQUIRE(view.size() == 1);
}

TEST_CASE("View cache", "[View]")
{
	Scene scene;
	scene.addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<ControllableComponent>();
	auto &view = scene.view<PositionComponent>();
	REQUIRE(&view == &scene.view<PositionComponent>());
}

TEST_CASE("View cache switch", "[View]")
{
	Scene scene;
	scene.addEntity("player")
		.addComponent<PositionComponent>()
		.addComponent<ControllableComponent>();
	auto &view = scene.view<PositionComponent>();
	Scene scene2;
	scene2.addEntity("box")
		.addComponent<PositionComponent>();

	REQUIRE(&view == &scene.view<PositionComponent>());
	REQUIRE(view.entities.begin()->get().getName() == "player");
	REQUIRE(scene2.view<PositionComponent>().entities.begin()->get().getName() == "box");
}

//TEST_CASE("View iteration", "[View]")
//{
//	Scene scene;
//	scene.addEntity("player")
//		.addComponent<PositionComponent>()
//		.addComponent<ControllableComponent>();
//	scene.addEntity("Box")
//		.addComponent<PositionComponent>();
//	int i = 0;
//	for (auto &entity : scene.view<PositionComponent>()) {
//		if (i == 0)
//			REQUIRE(entity.getName() == "player");
//		else
//			REQUIRE(entity.getName() == "Box");
//	}
//}