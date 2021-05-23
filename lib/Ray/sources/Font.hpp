/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_

#include <raylib.h>
#include "IRessource.hpp"

namespace RAY
{
	//! @brief A font manager
	class Font: public IRessource {
		public:
			//! @brief Create an font, loading a file
			//! @param filename: path to file to load
			Font(const std::string &filename);

			//! @brief A default copy constructor
			Font(const Font &) = default;

			//! @brief A default constructor, no ressources loaded
			Font();

			//! @brief An font is assignable
			Font &operator=(const Font &) = default;
			
			//! @brief Unload font at destruction
			~Font();

			//! @brief load font from file
			//! @param filename: path of input
			bool load(const std::string &filename);

			//! @brief unload ressources
			bool unload();

		protected:
		private:
			//! @brief Font, really, that's just it...
			::Font _font;
	};   
}

#endif