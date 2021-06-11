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
#include "ParserYaml.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;

namespace BBM {

	std::string ParserYAML::_block = "\nblocks:";
	std::string ParserYAML::_bonus = "\nbonuses:";
	std::string ParserYAML::_player = "players:";

	const char *ParserYAML::_getBlockType(std::string blockName)
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

		return (std::to_string(map.at(blockName)).c_str());
	}

	void ParserYAML::_saveBonus(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto name = entity.getName();

		if (!position)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_bonus.append("\n\t" + name + ":\n\t\t");
		_bonus.append("position:\n\t\t\t");
		_bonus.append("x: " + std::to_string(position->getX()) + "\n\t\t\t");
		_bonus.append("y: " + std::to_string(position->getY()) + "\n\t\t\t");
		_bonus.append("z: " + std::to_string(position->getZ()));
	}

	void ParserYAML::_savePlayer(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto *bombHolder = entity.tryGetComponent<BombHolderComponent>();
		auto name = entity.getName();

		if (!position || !bombHolder)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_player.append("\n\t" + name + ":\n\t\t");
		_player.append("max_bomb: " + std::to_string(bombHolder->maxBombCount) + "\n\t\t");
		_player.append("explosion_radius: " + std::to_string(bombHolder->explosionRadius) + "\n\t\t");
		_player.append("position:\n\t\t\t");
		_player.append("x: " + std::to_string(position->getX()) + "\n\t\t\t");
		_player.append("y: " + std::to_string(position->getY()) + "\n\t\t\t");
		_player.append("z: " + std::to_string(position->getZ()));
	}

	void ParserYAML::_saveBlock(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto name = entity.getName();

		if (!position)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_block.append("\n\t" + name + ":\n\t\t");
		_block.append(std::string("block_type: ") + _getBlockType(entity.getName()) + "\n\t\t");
		_block.append("position:\n\t\t\t");
		_block.append("x: " + std::to_string(position->getX()) + "\n\t\t\t");
		_block.append("y: " + std::to_string(position->getY()) + "\n\t\t\t");
		_block.append("z: " + std::to_string(position->getZ()));
	}

	void ParserYAML::save(std::shared_ptr<WAL::Scene> scene, std::string &filename)
	{
		std::string path = std::string("save/" + filename);
		std::map<std::string, std::function<void (const WAL::Entity &)>> savingGame = {
				{"Bonus", &_saveBonus},
				{"Block", &_saveBlock},
				{"Floor", &_saveBlock},
				{"Wall", &_saveBlock},
				{"Player", &_savePlayer}
		};
		std::ofstream file(path.c_str());
		for (const auto &entity : scene->getEntities()) {
			for (const auto& type : savingGame) {
				if (entity.getName().find(type.first) != std::string::npos) {
					type.second(entity);
				}
			}
		}
		file << _player << _block << _bonus << std::endl;
	}

	void ParserYAML::loadPlayers(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{

	}

	void ParserYAML::loadBlocks(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{

	}

	void ParserYAML::loadBonuses(std::shared_ptr<WAL::Scene> scene, std::string filename)
	{

	}

	void ParserYAML::load(std::shared_ptr<WAL::Scene> scene, std::string &filename)
	{
		std::map<std::string, std::vector<std::string>> parser = {
			{"players", {}},
			{"blocks", {}},
			{"bonuses", {}}
		};
		std::ifstream file("save/" + filename);
		if (file.good()) {
			std::string line;
			while (std::getline(file, line)) {

			}
		}
	}

	Vector3f ParserYAML::getPosition(std::string &filename)
	{

		return Vector3f();
	}

	unsigned int ParserYAML::getMaxBomb(std::string &filename)
	{
		return 0;
	}

	float ParserYAML::getExplosionRadius(std::string &filename)
	{
		return 0;
	}
}