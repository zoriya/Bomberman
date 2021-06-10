//
// Created by hbenjamin on 10/06/2021.
//

#include <fstream>
#include <map>
#include <Component/Position/PositionComponent.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include <Map/Map.hpp>
#include "ParserYaml.hpp"

namespace BBM {

	std::string ParserYAML::_block = "blocks:\n\t";
	std::string ParserYAML::_bonus = "bonuses:\n\t";
	std::string ParserYAML::_player = "players:\n\t";

	char *_getBlockType(std::string blockName)
	{
		static std::map<std::string, MapGenerator::BlockType> map {
			{"Upper Floor", MapGenerator::BlockType::UPPERFLOOR},
			{"Bottom Wall", MapGenerator::BlockType::UNBREAKABLE},
			{"Upper Wall", MapGenerator::BlockType::UNBREAKABLE},
			{"Left Wall", MapGenerator::BlockType::UNBREAKABLE},
			{"Right Wall", MapGenerator::BlockType::UNBREAKABLE},
			{"Bumper Block", MapGenerator::BlockType::BUMPER},
			{"Breakable Block", MapGenerator::BlockType::BREAKABLE},
			{"Unbreakable Block", MapGenerator::BlockType::UNBREAKABLE},
			{"Unbreakable Wall", MapGenerator::BlockType::FLOOR},
			{"Hole Block", MapGenerator::BlockType::HOLE}
		};

		return (std::string(map.at(blockName)));
	}

	void ParserYAML::_saveBonus(WAL::Entity entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();

		if (!position)
			return;
		_bonus.append(entity.getName() + ":\n\t\t");
		_bonus.append("position:\n\t\t\t");
		_bonus.append("x: " + std::to_string(position->getX()) + "\n\t\t\t");
		_bonus.append("y: " + std::to_string(position->getY()) + "\n\t\t\t");
		_bonus.append("z: " + std::to_string(position->getZ()) + "\n");
	}

	void ParserYAML::_savePlayer(WAL::Entity entity)
	{

	}

	void ParserYAML::_saveBlock(WAL::Entity entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();

		if (!position)
			return;
		_block.append(entity.getName() + ":\n\t\t");
		_block.append(std::string("block_type: ") + _getBlockType(entity.getName()) + "\n\t\t");
		_block.append("position:\n\t\t\t");
		_block.append("x: " + std::to_string(position->getX()) + "\n\t\t\t");
		_block.append("y: " + std::to_string(position->getY()) + "\n\t\t\t");
		_block.append("z: " + std::to_string(position->getZ()) + "\n");
	}

	void ParserYAML::save(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{
		std::string path = std::string("save/" + filename);
		std::map<std::string, std::function<void (WAL::Entity)>> savingGame = {
				{"Bonus", &_saveBonus},
				{"Block", &_saveBlock},
				{"Floor", &_saveBlock},
				{"Wall", &_saveBlock},
				{"Player", &_savePlayer}
		};
		std::ofstream file(path.c_str());
		for (auto entity : scene->getEntities()) {
			for (auto type : savingGame) {
				if (entity.getName().find(type.first) != std::string::npos) {
					type.second(entity);
				}
			}
		}
	}
}