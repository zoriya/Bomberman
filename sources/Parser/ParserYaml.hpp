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

		//! @brief The number of chars for endl
		#ifdef _WIN32
			static constexpr int endlNbChars = 2;
		#else
			static constexpr int endlNbChars = 1;
		#endif

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
		static std::string _getBlockType(const std::string& blockName);
		//!@param blockName bonus name
		//!@brief transform bonus name
		static std::string _getBonusType(const std::string& bonusName);

		//!@param str to parse
		//!@brief return max bomb parsed
		static int _parseMaxBomb(const std::string& str);
		//!@param line to parse
		//!@brief return explosion radius parsed
		static int _parseExplosionRadius(const std::string& line);
		//!@param line to parse
		//!@brief return speed parsed
		static float _parseSpeed(const std::string& line);
		//!@param line to parse
		//!@brief return vector3f of position parsed
		static Vector3f _parsePosition(const std::string& line);
		//!@param blockType to parse
		//!@brief return BlockType of type parsed
		static MapGenerator::BlockType _parseBlockType(const std::string& blockType);
		//!@param bonusType to parse
		//!@brief return bonusType of type parsed
		static Bonus::BonusType _parseBonusType(const std::string& bonusType);

		//!@param scene Scene to update
		//!@param lines Lines of the file
		//!@param index index of the vector
		//!@brief add player into scene
		static void _loadPlayer(std::shared_ptr<WAL::Scene> scene, Node &node, int countPlayer);
		//!@param scene Scene to update
		//!@param lines Lines of the file
		//!@param index index of the vector
		//!@param map map of all the block
		//!@brief add block into scene
		static void _loadBlock(std::shared_ptr<WAL::Scene> scene, Node child, MapGenerator::MapBlock &map);
		//!@param scene Scene to update
		//!@param lines Lines of the file
		//!@param index index of the vector
		//!@brief add bonus into scene
		static void _loadBonus(std::shared_ptr<WAL::Scene> scene, Node &node);

		//!@param scene Scene to update
		//!@brief load all players into scene
		static void _loadPlayers(std::shared_ptr<WAL::Scene> scene, Node &node);
		//!@param scene Scene to update
		//!@brief load all blocks into scene
		static void _loadBlocks(std::shared_ptr<WAL::Scene> scene, Node &node);
		//!@param scene Scene to update
		//!@brief load all blocks into scene
		static void _loadBonuses(std::shared_ptr<WAL::Scene> scene, Node &node);

		static std::string parseHeader(const std::string &line);

		static std::pair<std::string ,std::string> parseProperty(const std::string &line);

		static bool isHeader(const std::string &line);

		static Node parseNode(std::ifstream &file, const std::string &nodeName, int indentLevel = 0);

		static float getIndent(const std::string &line);

		static constexpr const char* indent = "  ";

	public:

		static Node parseFile(const std::string &path);

		struct PlayerInfos {
			std::string name;
			//! @brief Player position
			Vector3f position;
			//! @brief The amount of bomb a player had
			int maxBombCount;
			//! @brief The explosion range of a player
			int explosionRange;
			//! @brief The speed of a player
			float speed;
			//! @brief The assets of the player
			std::string asset;
		};

		static std::vector<PlayerInfos> playersInfos;

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