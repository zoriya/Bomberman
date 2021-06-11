//
// Created by hbenjamin on 10/06/2021.
//

#pragma once

#include <Wal.hpp>

namespace BBM {
	class ParserYAML {
	private:
		static std::string _block;
		static std::string _bonus;
		static std::string _player;

		static void _saveBlock(const WAL::Entity &entity);
		static void _saveBonus(const WAL::Entity &entity);
		static void _savePlayer(const WAL::Entity &entity);
		static const char *_getBlockType(std::string blockName);
		static Vector3f getPosition(std::string &filename);
		static unsigned int getMaxBomb(std::string &filename);
		static float getExplosionRadius(std::string &filename);

		static void loadPlayers(std::shared_ptr<WAL::Scene> scene, std::string filename);
		static void loadBlocks(std::shared_ptr<WAL::Scene> scene, std::string filename);
		static void loadBonuses(std::shared_ptr<WAL::Scene> scene, std::string filename);
	public:
		static void save(std::shared_ptr<WAL::Scene> scene, std::string &filename);
		static void load(std::shared_ptr<WAL::Scene> scene, std::string &filename);

	};
}