/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Ressource
*/

#ifndef RESSOURCE_HPP_
#define RESSOURCE_HPP_

#include <string>

namespace RAY {
	//! @brief A Ressource interface
	class IRessource {
		public:
			virtual ~IRessource() = default;

			virtual bool load(const std::string &filePath) = 0;

			virtual bool unload() = 0;
	};
};

#endif /* !RESSOURCE_HPP_ */
