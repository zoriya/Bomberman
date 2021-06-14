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
		static std::string _block;
		static std::string _bonus;
		static std::string _player;

		static void _saveBlock(const WAL::Entity &entity);
		static void _saveBonus(const WAL::Entity &entity);
		static void _savePlayer(const WAL::Entity &entity);
		static std::string _getBlockType(std::string blockName);
		static std::string _getBonusType(std::string bonusName);

		static WAL::Entity &_parseEntityName(std::string line, WAL::Entity &entity);
		static int _parseMaxBomb(std::string &filename);
		static float _parseExplosionRadius(std::string &filename);
		static Vector3f _parsePosition(std::string &filename);
		static MapGenerator::BlockType _parseBlockType(std::string blockType);
		static Bonus::BonusType _parseBonusType(std::string bonusType);

		static void _loadPlayer(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index);
		static void _loadBlock(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index, MapGenerator::MapBlock &map);
		static void _loadBonus(std::shared_ptr<WAL::Scene> scene, std::vector<std::string> lines, int &index);

		static void _loadPlayers(std::shared_ptr<WAL::Scene> scene, std::string filename);
		static void _loadBlocks(std::shared_ptr<WAL::Scene> scene, std::string filename);
		static void _loadBonuses(std::shared_ptr<WAL::Scene> scene, std::string filename);
	public:
		static void save(std::shared_ptr<WAL::Scene> scene, std::string filename);
		static void load(std::shared_ptr<WAL::Scene> scene, std::string filename);

	};
}