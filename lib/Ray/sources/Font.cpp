/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Font
*/

#include "Font.hpp"

RAY::Cache<::Font> RAY::Font::_fontsCache(LoadFont, UnloadFont);

RAY::Font::Font(const std::string &filename, bool lonely):
	_font(_fontsCache.fetch(filename, lonely))
{
}

RAY::Font::Font():
	_font(std::make_shared<::Font>())
{
}
