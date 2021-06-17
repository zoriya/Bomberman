/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Font
*/

#include "Font.hpp"

RAY::Cache<::Font> RAY::Font::_fontsCache([] (const char *str) {
		::Font font = LoadFont(str);

		if (font.texture.id <= 0)
			throw Exception::ResourceNotFound(std::string(str));
		return font;
	}, UnloadFont);

RAY::Font::Font(const std::string &filename, bool lonely):
	_font(_fontsCache.fetch(filename, lonely))
{
}

RAY::Font::Font():
	_font(std::make_shared<::Font>())
{
}
