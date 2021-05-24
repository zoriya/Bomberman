//
// Created by Zoe Roux on 5/17/21.
//


#include "Wal.hpp"
#include "System/Movable/MovableSystem.hpp"
#include <catch2/catch.hpp>

using namespace WAL;
using namespace Bomberman;

TEST_CASE("Create system", "[Engine][System]")
{
	Wal wal;
	wal.addSystem<MovableSystem>();

	SECTION("Check existence") {
		REQUIRE_NOTHROW(wal.getSystem<MovableSystem>());
	}
	SECTION("Duplicate check") {
		REQUIRE_THROWS_AS(wal.addSystem<MovableSystem>(), DuplicateError);
	}
	SECTION("Remove system") {
		wal.removeSystem<MovableSystem>();
		REQUIRE_THROWS_AS(wal.getSystem<MovableSystem>(), NotFoundError);
		REQUIRE_THROWS_AS(wal.removeSystem<MovableSystem>(), NotFoundError);
	}
}

TEST_CASE("Create system by reference", "[Engine][System]")
{
	Wal wal;
	MovableSystem system;
	wal.addSystem(system);
	REQUIRE_THROWS_AS(wal.addSystem<MovableSystem>(), DuplicateError);
}