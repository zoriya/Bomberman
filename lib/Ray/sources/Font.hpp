/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_

#include <raylib.h>
#include <string>
#include "Utils/Cache.hpp"

namespace RAY
{
	//! @brief A font manager
	class Font {
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
			
			//! @brief Default destructor
			~Font() = default;

		protected:
		private:
			//! @brief Font, really, that's just it...
			std::shared_ptr<::Font> _font;

			static Cache<::Font> _fontsCache;
	};   
}

#endif