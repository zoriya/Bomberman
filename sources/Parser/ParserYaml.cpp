//
// Created by hbenjamin on 10/06/2021.
//

#include <fstream>
#include "ParserYaml.hpp"

namespace BBM {
	void ParserYAML::save(std::shared_ptr<WAL::Scene> scene, std::string filename) {
		std::string path = std::string("save/" + filename);
		std::ofstream file(path.c_str());
		for (auto entity : scene->getEntities()) {

		}
	}
}