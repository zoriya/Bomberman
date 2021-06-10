//
// Created by hbenjamin on 10/06/2021.
//

#pragma once

#include <Wal.hpp>

namespace BBM {
	class ParserYAML {
	public:
		static void save(std::shared_ptr<WAL::Scene> scene, std::string filename);
	};
}