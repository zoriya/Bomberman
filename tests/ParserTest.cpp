//
// Created by hbenjamin on 11/06/2021.
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
#include "Component/BombHolder/BombHolderComponent.hpp"
#include "Parser/ParserYaml.hpp"

using namespace WAL;
using namespace BBM;

TEST_CASE("Parser Test", "[PARSER]")
{
	Wal wal;
	wal.changeScene(std::make_shared<Scene>());
	wal.getScene()->addEntity("Player")
		.addComponent<ControllableComponent>()
		.addComponent<MovableComponent>()
		.addComponent<BombHolderComponent>()
		.addComponent<PositionComponent>();
	wal.getScene()->addEntity("Bonus Fire Up")
		.addComponent<PositionComponent>(2, 0, 2);
	wal.getScene()->addEntity("Breakable Block")
		.addComponent<PositionComponent>(1, 0, 1);
	wal.getScene()->addEntity("Unbreakable Block")
			.addComponent<PositionComponent>(1, 5, 1);
	ParserYAML::save(wal.getScene(), "test_filename.yml");
}