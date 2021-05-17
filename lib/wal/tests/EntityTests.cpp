//
// Created by Zoe Roux on 5/17/21.
//

#include <catch2/catch.hpp>
#include "Entity/Entity.hpp"
#include "Component/Basics/PositionComponent.hpp"

using namespace WAL;
using namespace WAL::Components;

TEST_CASE("Component", "[Entity]")
{
	Entity entity("Bob");
	entity.addComponent<PositionComponent>(2, 3, 4);

	SECTION("Check value") {
		auto &pos = entity.getComponent<PositionComponent>();
		REQUIRE(entity.hasComponent<PositionComponent>());
		REQUIRE(pos.getPosition() == Vector3f(2, 3, 4));
	}
	SECTION("Prevent duplicates") {
		REQUIRE_THROWS_AS(entity.addComponent<PositionComponent>(), DuplicateError);
	}
}

TEST_CASE("ComponentNotFound", "[Entity]")
{
	Entity entity("Bob");
	REQUIRE_THROWS_AS(entity.getComponent<PositionComponent>(), NotFoundError);
}