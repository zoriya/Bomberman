//
// Created by hbenjamin on 10/06/2021.
//

#include <fstream>
#include <map>
#include <Component/Position/PositionComponent.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include <Map/Map.hpp>
#include <Component/BombHolder/BombHolderComponent.hpp>
#include <sstream>
#include <Component/Controllable/ControllableComponent.hpp>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <Component/Shaders/ShaderComponent.hpp>
#include <Component/Animator/AnimatorComponent.hpp>
#include <Component/Tag/TagComponent.hpp>
#include <Component/Animation/AnimationsComponent.hpp>
#include <Component/Sound/SoundComponent.hpp>
#include <Component/Bonus/PlayerBonusComponent.hpp>
#include <Component/Music/MusicComponent.hpp>
#include <Items/Bonus.hpp>
#include <Exception/Error.hpp>
#include "ParserYaml.hpp"
#include <algorithm>

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM {

	std::string ParserYAML::_block = "blocks:";
	std::string ParserYAML::_bonus = "bonuses:";
	std::string ParserYAML::_player = "players:";

	std::string ParserYAML::_getBlockType(std::string blockName)
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

		return (std::to_string(map.at(blockName)));
	}

	std::string ParserYAML::_getBonusType(std::string bonusName)
	{
		static std::map<std::string, Bonus::BonusType> map {
			{"Bonus Bomb Up", Bonus::BonusType::BOMBSTOCK},
			{"Bonus Speed Up", Bonus::BonusType::SPEEDUP},
			{"Bonus Fire Up", Bonus::BonusType::EXPLOSIONINC}
		};

		return (std::to_string(map.at(bonusName)));
	}

	void ParserYAML::_saveBonus(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto name = entity.getName();

		if (!position)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_bonus.append("\n  " + name + ":\n    ");
		_bonus.append(std::string("bonus_type: ") + _getBonusType(entity.getName()) + "\n    ");
		_bonus.append("position: [" + std::to_string(position->getX()) + " " + std::to_string(position->getY()) + " " + std::to_string(position->getZ()) + "]");
	}

	void ParserYAML::_savePlayer(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto *bombHolder = entity.tryGetComponent<BombHolderComponent>();
		auto name = entity.getName();

		if (!position || !bombHolder)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_player.append("\n  " + name + ":\n    ");
		_player.append("max_bomb: " + std::to_string(bombHolder->maxBombCount) + "\n        ");
		_player.append("explosion_radius: " + std::to_string(bombHolder->explosionRadius) + "\n        ");
		_player.append("position: [" + std::to_string(position->getX()) + " " + std::to_string(position->getY()) + " " + std::to_string(position->getZ()) + "]");
	}

	void ParserYAML::_saveBlock(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto name = entity.getName();

		if (!position)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_block.append("\n  " + name + ":\n    ");
		_block.append(std::string("block_type: ") + _getBlockType(entity.getName()) + "\n    ");
		_block.append("position: [" + std::to_string(position->getX()) + " " + std::to_string(position->getY()) + " " + std::to_string(position->getZ()) + "]");
	}

	void ParserYAML::save(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{
		std::string block = std::string("save/" + filename + "_block.yml");
		std::string player = std::string("save/" + filename + "_player.yml");
		std::string bonus = std::string("save/" + filename + "_bonus.yml");
		std::map<std::string, std::function<void (const WAL::Entity &)>> savingGame = {
				{"Bonus", &_saveBonus},
				{"Block", &_saveBlock},
				{"Floor", &_saveBlock},
				{"Wall", &_saveBlock},
				{"Player", &_savePlayer}
		};
		std::ofstream blockFile(block.c_str());
		std::ofstream playerFile(player.c_str());
		std::ofstream bonusFile(bonus.c_str());
		for (const auto &entity : scene->getEntities()) {
			for (const auto& type : savingGame) {
				if (entity.getName().find(type.first) != std::string::npos) {
					type.second(entity);
				}
			}
		}
		blockFile << _block << std::endl;
		playerFile << _player << std::endl;
		bonusFile << _bonus << std::endl;
		_block.clear();
		_player.clear();
		_bonus.clear();
	}

	std::string ParserYAML::_parseEntityName(std::string line)
	{
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		return (line.substr(0, line.find(':')));
	}

	void ParserYAML::_loadPlayers(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{
		std::ifstream file("save/" + filename + "_player.yml");
		if (file.good()) {
			std::string line;
			while (std::getline(file, line)) {
			}
		}
	}

	void ParserYAML::_loadBlocks(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{
		std::ifstream file("save/" + filename + "_player.yml");
		if (file.good()) {
			std::string line;
			while (std::getline(file, line)) {
			}
		}
	}

	void ParserYAML::_loadBonuses(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{
		static std::map<Bonus::BonusType, std::vector<std::string>> map = {
				{Bonus::BonusType::BOMBSTOCK, {"Bonus Bomb Up", "assets/items/bombup"}},
				{Bonus::BonusType::SPEEDUP, {"Bonus Speed Up", "assets/items/speedup"}},
				{Bonus::BonusType::EXPLOSIONINC, {"Bonus Fire Up", "assets/items/fireup"}}
		};
		static std::vector<std::function<void (WAL::Entity &, const WAL::Entity &, CollisionComponent::CollidedAxis)>> func = {
				&Bonus::BombUpBonus, &Bonus::SpeedUpBonus, &Bonus::ExplosionRangeBonus
		};
		WAL::Entity entity(*scene, "");

		std::ifstream file("save/" + filename + "_bonus.yml");
		if (file.good()) {
			std::string line;
			while (std::getline(file, line)) {

			}
		}
	}

	void ParserYAML::load(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{
		_loadBlocks(scene, filename);
		_loadBonuses(scene, filename);
		_loadPlayers(scene, filename);
	}

	WAL::Entity &ParserYAML::_parsePosition(std::string &line, WAL::Entity &entity) {
		std::string x;
		std::string y;
		std::string z;
		std::string subStr;

		try {
			subStr = line.substr(line.find("position: [", 0), line.length());
			x = subStr.substr(0, subStr.find(' '));
			y = subStr.substr(x.length() + 1, subStr.find(' '));
			z = subStr.substr(x.length() + y.length() + 2, subStr.find(']'));
		} catch (const std::out_of_range &err) {
			throw (ParserError("Error parsing position"));
		}
		return entity.addComponent<PositionComponent>(Vector3f(std::atof(x.c_str()), std::atof(y.c_str()), std::atof(z.c_str())));
	}

	WAL::Entity &ParserYAML::_parseMaxBomb(std::string &line, WAL::Entity &entity)
	{
		auto *bombHolder = entity.tryGetComponent<BombHolderComponent>();

		if (line.find(": ") == std::string::npos)
			throw (ParserError("Couldn't parse max bomb"));
		if (bombHolder) {
			bombHolder->maxBombCount = std::atoi(line.substr(line.find(": ")).c_str());
			return (entity);
		}
		return (entity.addComponent<BombHolderComponent>(std::atoi(line.substr(line.find(": ")).c_str())));
	}

	WAL::Entity &ParserYAML::_parseExplosionRadius(std::string &line, WAL::Entity &entity)
	{
		auto *bombHolder = entity.tryGetComponent<BombHolderComponent>();

		if (line.find(": ") == std::string::npos)
			throw (ParserError("Couldn't parse explosion radius"));
		if (bombHolder) {
			bombHolder->explosionRadius = std::atoi(line.substr(line.find(": ")).c_str());
			return (entity);
		}
		return (entity.addComponent<BombHolderComponent>(3, bombHolder->explosionRadius = std::atoi(line.substr(line.find(": ")).c_str())));
	}

	MapGenerator::BlockType _parseBlockType(std::string blockType)
	{
		if (blockType.find(": ") == std::string::npos)
			throw (ParserError("Couldn't parse block type"));
		return (static_cast<MapGenerator::BlockType>(std::atoi(blockType.substr(blockType.find(": ")).c_str())));
	}

	static Bonus::BonusType _parseBonusType(std::string bonusType)
	{
		if (bonusType.find(": ") == std::string::npos)
			throw (ParserError("Couldn't parse bonus type"));
		return (static_cast<MapGenerator::BlockType>(std::atoi(bonusType.substr(bonusType.find(": ")).c_str())));
	}
}