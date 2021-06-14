//
// Created by hbenjamin on 10/06/2021.
//

#pragma once

#include <Wal.hpp>
#include "Items/Bonus.hpp"
#include "Map/Map.hpp"

namespace BBM {
	class ParserYAML {
	private:

		//!@brief file block of the parser
		static std::string _block;
		//!@brief file bonus of the parser
		static std::string _bonus;
		//!@brief file player of the parser
		static std::string _player;

		//!@param entity entity to save
		//!@brief save block in _block
		static void _saveBlock(const WAL::Entity &entity);
		//!@param entity entity to save
		//!@brief save bonus in _bonus
		static void _saveBonus(const WAL::Entity &entity);
		//!@param entity entity to save
		//!@brief save player in _player
		static void _savePlayer(const WAL::Entity &entity);
		//!@param blockName block name
		//!@brief transform block name
		static std::string _getBlockType(std::string blockName);
		//!@param blockName bonus name
		//!@brief transform bonus name
		static std::string _getBonusType(std::string bonusName);

		//!@param line to parse
		//!@param entity to update
		//!@brief parse entity name
		static WAL::Entity &_parseEntityName(std::string line, WAL::Entity &entity);
		//!@param line to parse
		//!@brief return max bomb parsed
		static int _parseMaxBomb(std::string &filename);
		//!@param line to parse
		//!@brief return explosion radius parsed
		static float _parseExplosionRadius(std::string &filename);
		//!@param line to parse
		//!@brief return vector3f of position parsed
		static Vector3f _parsePosition(std::string &filename);
		//!@param blockType to parse
		//!@brief return BlockType of type parsed
		static MapGenerator::BlockType _parseBlockType(std::string blockType);
		//!@param bonusType to parse
		//!@brief return bonusType of type parsed
		static Bonus::BonusType _parseBonusType(std::string bonusType);

		//!@param scene Scene to update
		//!@param lines Lines of the file
		//!@param index index of the vector
		//!@brief add player into scene
		static void _loadPlayer(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index);
		//!@param scene Scene to update
		//!@param lines Lines of the file
		//!@param index index of the vector
		//!@param map map of all the block
		//!@brief add block into scene
		static void _loadBlock(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index, MapGenerator::MapBlock &map);
		//!@param scene Scene to update
		//!@param lines Lines of the file
		//!@param index index of the vector
		//!@brief add bonus into scene
		static void _loadBonus(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index);

		//!@param scene Scene to update
		//!@param filename filename of the file to read
		//!@brief load all players into scene
		static void _loadPlayers(std::shared_ptr<WAL::Scene> scene, std::string filename);
		//!@param scene Scene to update
		//!@param filename filename of the file to read
		//!@brief load all blocks into scene
		static void _loadBlocks(std::shared_ptr<WAL::Scene> scene, std::string filename);
		//!@param scene Scene to update
		//!@param filename filename of the file to read
		//!@brief load all blocks into scene
		static void _loadBonuses(std::shared_ptr<WAL::Scene> scene, std::string filename);
	public:
		//!@param scene Scene to update
		//!@param filename filename of the file to read
		//!@brief save yaml
		static void save(std::shared_ptr<WAL::Scene> scene, std::string filename);
		//!@param scene Scene to update
		//!@param filename filename of the file to read
		//!@brief load yaml
		static void load(std::shared_ptr<WAL::Scene> scene, std::string filename);

	};
}