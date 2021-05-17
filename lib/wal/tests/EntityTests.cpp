//
// Created by Zoe Roux on 5/17/21.
//

#include <catch2/catch.hpp>
#include "Entity/Entity.hpp"
#include "Component/Basics/PositionComponent.hpp"

using namespace WAL;
using namespace WAL::Components;

TEST_CASE("Get component", "[Entity/getComponent]")
{
	Entity entity("Bob");
	entity.addComponent<PositionComponent>();
}