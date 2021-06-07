//
// Created by Zoe Roux on 5/17/21.
//

#include "Entity/Entity.hpp"
#include "Component/Position/PositionComponent.hpp"
#include <catch2/catch.hpp>
#include <Wal.hpp>
#include <Scene/Scene.hpp>

using namespace WAL;
using namespace BBM;

TEST_CASE("Component", "[Entity]")
{
	Scene scene;
	Entity entity(scene, "Bob");
	entity.addComponent<PositionComponent>(2, 3, 4);

	SECTION("Check value") {
		auto &pos = entity.getComponent<PositionComponent>();
		REQUIRE(entity.hasComponent<PositionComponent>());
		REQUIRE(pos.position == Vector3f(2, 3, 4));
	}
	SECTION("Prevent duplicates") {
		REQUIRE_THROWS_AS(entity.addComponent<PositionComponent>(), DuplicateError);
	}
	SECTION("Remove component") {
		entity.removeComponent<PositionComponent>();
		REQUIRE_THROWS_AS(entity.getComponent<PositionComponent>(), NotFoundError);
		REQUIRE_THROWS_AS(entity.removeComponent<PositionComponent>(), NotFoundError);
	}
}

TEST_CASE("ComponentNotFound", "[Entity]")
{
	Scene scene;
	Entity entity(scene, "Bob");
	REQUIRE_THROWS_AS(entity.getComponent<PositionComponent>(), NotFoundError);
}

TEST_CASE("Add component by reference", "[Entity]")
{
	Scene scene;
	Entity entity(scene, "Bob");
	PositionComponent component(entity, 4, 5, 6);

	REQUIRE(&entity.addComponent(component) == &entity);
	REQUIRE(entity.getComponent<PositionComponent>().position == Vector3f(4, 5, 6));
}