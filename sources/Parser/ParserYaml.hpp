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

		static void _saveBlock(WAL::Entity entity);
		static void _saveBonus(WAL::Entity entity);
		static void _savePlayer(WAL::Entity entity);
		static char *_getBlockType(std::string blockName);
	public:
		static void save(std::shared_ptr<WAL::Scene> scene, std::string filename);
	};
}