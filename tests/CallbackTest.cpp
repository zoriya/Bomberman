//
// Created by Zoe Roux on 5/21/21.
//

#include <catch2/catch.hpp>
#include <stdexcept>
#include <Wal.hpp>
#include "Entity/Entity.hpp"
#include "Models/Callback.hpp"

using namespace WAL;

TEST_CASE("Callback basic test", "[Callback]")
{
	Callback<std::string> callback;

	REQUIRE_NOTHROW(callback("1"));
	SECTION("Check add") {
		int id = callback.addCallback([](const std::string& i) {
			if (i == "Super")
				throw std::runtime_error(i);
		});
		REQUIRE_THROWS_AS(callback("Super"), std::runtime_error);

		SECTION("Check remove") {
			REQUIRE(id == 0);
			callback.removeCallback(id);
			REQUIRE_NOTHROW(callback("Super"));
		}
	}
}

TEST_CASE("Callback multiple arguments", "[Callback]")
{
	Callback<std::string, int, unsigned *, Entity &> callback;

	callback.addCallback([](const std::string& str, int a, unsigned *value, Entity &entity) {
		throw std::runtime_error("");
	});
	Wal wal;
	Entity entity(wal, "name");
	REQUIRE_THROWS_AS(callback("1", 0, nullptr, entity), std::runtime_error);
}
