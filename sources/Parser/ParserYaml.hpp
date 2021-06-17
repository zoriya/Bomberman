//
// Created by hbenjamin on 10/06/2021.
//

#pragma once

#include <Wal.hpp>
#include "Items/Bonus.hpp"
#include "Node.hpp"
#include "Map/Map.hpp"
#include "Component/Controllable/ControllableComponent.hpp"

namespace BBM {
	class ParserYAML {
	private:

		//!@brief file block of the parser
		static std::stringstream _block;
		//!@brief file bonus of the parser
		static std::stringstream _bonus;
		//!@brief file player of the parser
		static std::stringstream _player;

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
		static int _parseMaxBomb(std::string &line);
		//!@param line to parse
		//!@brief return explosion radius parsed
		static float _parseExplosionRadius(std::string &line);
		//!@param line to parse
		//!@brief return speed parsed
		static float _parseSpeed(std::string &line);
		//!@param line to parse
		//!@brief return vector3f of position parsed
		static Vector3f _parsePosition(std::string &line);
		//!@param blockType to parse
		//!@brief return BlockType of type parsed
		static MapGenerator::BlockType _parseBlockType(std::string &blockType);
		//!@param bonusType to parse
		//!@brief return bonusType of type parsed
		static Bonus::BonusType _parseBonusType(std::string &bonusType);
		//!@param assets to parse
		//!@brief return assets parsed
		static std::string _parseAssets(std::string &line);

		//!@param scene Scene to update
		//!@param lines Lines of the file
		//!@param index index of the vector
		//!@brief add player into scene
		static void _loadPlayer(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index, int countPlayer);
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
		//!@brief load all players into scene
		static void _loadPlayers(std::shared_ptr<WAL::Scene> scene);
		//!@param scene Scene to update
		//!@brief load all blocks into scene
		static void _loadBlocks(std::shared_ptr<WAL::Scene> scene, Node &node);
		//!@param scene Scene to update
		//!@brief load all blocks into scene
		static void _loadBonuses(std::shared_ptr<WAL::Scene> scene);

		static std::string parseHeader(const std::string &line);

		static std::pair<std::string ,std::string> parseProperty(const std::string &line);

		static bool isHeader(const std::string &line);

		static Node parseNode(std::ifstream &file, const std::string &nodeName, int indentLevel = 0);

		static float getIndent(const std::string &line);

		static constexpr const char* indent = "  ";

	public:

		static Node parseFile(const std::string &path);

		//! @brief All name that was into the file
		static std::vector<std::string> playerName;
		//! @brief Player position
		static std::vector<Vector3f> playerPosition;
		//! @brief The amount of bomb a player had
		static std::vector<int> playerBombCount;
		//! @brief The explosion range of a player
		static std::vector<float> playerExplosionRange;
		//! @brief The speed of a player
		static std::vector<float> playerSpeed;
		//! @brief The assets of the player
		static std::vector<std::string> playerAssets;

		//!@param scene Scene to update
		//!@brief save yaml
		static void save(std::shared_ptr<WAL::Scene> scene);
		//!@param scene Scene to update
		//!@brief load yaml
		static void load(std::shared_ptr<WAL::Scene> scene);

		//! @brief save file name
		static const std::string fileName;

	};
}